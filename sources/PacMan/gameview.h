#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "tilemanager.h"

class GameView : public QWidget
{
    Q_OBJECT
    public:
        explicit GameView(QWidget *parent = nullptr);
        //setmodel

    signals:

    public slots:

    private:
        QLabel * labyrinthe;
        QLabel * dynamic; // Ou une liste pour représenter chaque entités
};

#endif // GAMEVIEW_H
