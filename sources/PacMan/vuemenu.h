#ifndef VUEMENU_H
#define VUEMENU_H
#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class VueMenu;
}

class VueMenu : public QWidget
{
    Q_OBJECT

public:
    explicit VueMenu(QWidget *parent = 0);
    ~VueMenu();
    void setMainWindow(MainWindow *mainW);

private:
    Ui::VueMenu *ui;
    MainWindow *mw;


public slots:
    void on_play_as_guest_clicked();
    void on_load_profile_clicked();
    void on_create_profile_clicked();
};

#endif // VUEMENU_H
