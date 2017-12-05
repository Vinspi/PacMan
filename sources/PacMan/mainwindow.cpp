#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "vueprofile.h"
#include "profil.h"
#include "vuemenu.h"
#include "vuecreationprofil.h"
#include "gamescene.h"
#include <QGraphicsView>

#include <sstream>

using namespace std;

VueProfile *vp;
VueMenu *vm;
vuecreationprofil *vcp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gs = new GameScene(new TileManager("../PacMan/graphics_pacman/tileset.png"));

    gv = new GameView(gs);

    gs->setGameView(gv);

    ui->setupUi(this);
    /* on enleve les deux vue créée par le designer */
    QWidget* tmp = ui->stackedWidget->widget(0);
    ui->stackedWidget->removeWidget(tmp);

    tmp = ui->stackedWidget->widget(0);
    ui->stackedWidget->removeWidget(tmp);

    /* on créé le stack widget */


    /* on ajoute des element au QStackWidget */
    /* vue profil */
    vp = new VueProfile(this);
    vp->setMainWindow(this);
    vp->show();
    ui->stackedWidget->addWidget(vp);

    /* le menu */
    vm = new VueMenu();
    vm->setMainWindow(this);
    vm->show();

    vcp = new vuecreationprofil();
    vcp->setMainWindow(this);

    ui->stackedWidget->addWidget(vm);
    ui->stackedWidget->addWidget(gv);
    ui->stackedWidget->addWidget(vcp);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::launchGame(Profil *p, QString level){

    QString tileMap = "../PacMan/levels/";

    tileMap = tileMap+level;


    tm = new TileMap(tileMap);
    gs->init(*tm);
    gs->setActiveProfil(p);
    gv->show();

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::profileCreated(Profil *p){
     ui->stackedWidget->setCurrentIndex(0);
     vp->setProfil(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStackedWidget* MainWindow::getStackedWidget(){
    return ui->stackedWidget;
}


