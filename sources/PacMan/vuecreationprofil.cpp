#include "vuecreationprofil.h"
#include "ui_vuecreationprofil.h"
#include <iostream>
#include "profil.h"

vuecreationprofil::vuecreationprofil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vuecreationprofil)
{
    ui->setupUi(this);
}

vuecreationprofil::~vuecreationprofil()
{
    delete ui;
}

void vuecreationprofil::setMainWindow(MainWindow *w){
    this->mw = w;
}

void vuecreationprofil::on_submit_form_clicked(){
    QString pseudo = vuecreationprofil::ui->pseudo_input->toPlainText();
    if(pseudo.compare(new QString("")) != 0){
        Profil *p = new Profil(pseudo.toStdString());
        p->saveProfile("./profil");
        this->mw->profileCreated(p);
    }
}
