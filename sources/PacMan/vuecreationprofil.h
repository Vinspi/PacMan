#ifndef VUECREATIONPROFIL_H
#define VUECREATIONPROFIL_H

#include <QWidget>

#include "mainwindow.h"


namespace Ui {
class vuecreationprofil;
}

class vuecreationprofil : public QWidget
{
    Q_OBJECT

public:
    explicit vuecreationprofil(QWidget *parent = 0);
    ~vuecreationprofil();
    void setMainWindow(MainWindow *w);

public slots:
    void on_submit_form_clicked();

private:
    Ui::vuecreationprofil *ui;
    MainWindow *mw;
};

#endif // VUECREATIONPROFIL_H
