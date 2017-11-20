#ifndef VUEPROFILE_H
#define VUEPROFILE_H

#include <QWidget>
#include <QStackedWidget>

#include "profil.h"
#include "mainwindow.h"

namespace Ui {
class VueProfile;
}

class VueProfile : public QWidget
{
    Q_OBJECT

public:
    explicit VueProfile(QWidget *parent = 0);
    ~VueProfile();
    void setProfil(Profil *p);
    void setMainWindow(MainWindow *w);

public slots:
    void changeProfil();
    void selectLevel();
    void playlingLevelSelected();

private:
    Ui::VueProfile *ui;
    Profil* p;
    QString levelSelected;
    MainWindow *mw;


};

#endif // VUEPROFILE_H
