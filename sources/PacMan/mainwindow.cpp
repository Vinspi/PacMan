#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "vueprofile.h"
#include "profil.h"
#include "vuemenu.h"
#include "gamescene.h"
#include <QGraphicsView>

#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* on enleve les deux vue créée par le designer */
    QWidget* tmp = ui->stackedWidget->widget(0);
    ui->stackedWidget->removeWidget(tmp);

    tmp = ui->stackedWidget->widget(0);
    ui->stackedWidget->removeWidget(tmp);

    /* on créé le stack widget */


    /* on ajoute des element au QStackWidget */
    /* vue profil */
    VueProfile* vp = new VueProfile(this);
    vp->setMainWindow(this);
    vp->show();
    vp->setProfil(Profil::loadProfile("../PacMan/profil/pierre.pf"));
    ui->stackedWidget->addWidget(vp);

    /* le menu */
    VueMenu* vm = new VueMenu();
    vm->show();

    ui->stackedWidget->addWidget(vm);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::launchGame(QString level){
    GameScene* gs = new GameScene(new TileManager("../PacMan/graphics_pacman/tileset.png"));
            QString tileMap = "../PacMan/levels/";

            tileMap = tileMap+level;

//            tileMap.append(QString::number(level));
//            tileMap.append(".xml");

            std::printf("Level : %d", level);

            std::printf(tileMap.toStdString().c_str());

            TileMap tm(tileMap);
            gs->init(tm);
            QGraphicsView* gv = new QGraphicsView(gs);
            gv->show();
            ui->stackedWidget->addWidget(gv);
            ui->stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStackedWidget* MainWindow::getStackedWidget(){
    return ui->stackedWidget;
}


