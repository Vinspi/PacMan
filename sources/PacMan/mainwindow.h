#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "gamescene.h"
#include "gameview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStackedWidget* getStackedWidget();
    void launchGame(QString level);

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackedWidget;
    GameView* gv;
    GameScene* gs;
    TileMap *tm;
};

#endif // MAINWINDOW_H
