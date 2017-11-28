#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "tilemanager.h"
#include <QGraphicsView>
#include <QStackedWidget>

class GameView : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit GameView(QGraphicsScene *parent = nullptr);
        void setWid();

    signals:

    public slots:

    private:
        QStackedWidget *wid;

};

#endif // GAMEVIEW_H
