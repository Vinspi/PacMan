#include "vueprofil.h"
#include "ui_vueprofil.h"

VueProfil::VueProfil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VueProfil)
{
    ui->setupUi(this);
}

VueProfil::~VueProfil()
{
    delete ui;
}
