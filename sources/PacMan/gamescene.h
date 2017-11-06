#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include "tilemanager.h"
#include "tilemap.h"
#include "dotitem.h"
#include "const.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(TileManager *tm);
    //build scene from modele/level
    //
    void init(TileMap &map);// niveau
    void keyPressEvent(QKeyEvent *event);
    void checkCollisions();

public slots:

private:
    int score;
    TileManager * tm;
    //RessourceManager ?
    //Background
    QGraphicsPixmapItem * background;
    QGraphicsPixmapItem * labyrinthe;

    //Movable
    QGraphicsPixmapItem * Pacman;
    QGraphicsPixmapItem * PhantomRed;
    QGraphicsPixmapItem * PhantomPink;
    QGraphicsPixmapItem * PhantomBlue;
    QGraphicsPixmapItem * PhantomYellow;

    //Collectable
    QList<DotItem * > dots;
    QList<QGraphicsPixmapItem * > superDots;
    QGraphicsPixmapItem * fruit;

    //Game Info
    //QGraphicsTextItem * score;
    QGraphicsTextItem * level;
    //vies

};

#endif // GAMESCENE_H
