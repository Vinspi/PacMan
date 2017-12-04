#include "vuemenu.h"
#include "ui_vuemenu.h"


VueMenu::VueMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VueMenu)
{
    ui->setupUi(this);
}

void VueMenu::setMainWindow(MainWindow* mainW){
    mw = mainW;
}

VueMenu::~VueMenu()
{
    delete ui;
}

void VueMenu::on_play_as_guest_clicked(){
     mw->launchGame(new Profil("guest"), "xml_level1.xml");
}

void VueMenu::on_load_profile_clicked(){ 
    ((QStackedWidget*)this->parent())->setCurrentIndex(0);
}

void VueMenu::on_create_profile_clicked(){
     ((QStackedWidget*)this->parent())->setCurrentIndex(3);
}

