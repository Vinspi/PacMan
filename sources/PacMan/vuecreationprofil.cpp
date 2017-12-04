#include "vuecreationprofil.h"
#include "ui_vuecreationprofil.h"

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
