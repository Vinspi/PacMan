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
#include "superdotitem.h"
#include "collectableitem.h"
#include "entity.h"
#include "pacman.h"
#include <QTimer>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(TileManager *tm);
    //build scene from modele/level
    //
    void init(TileMap &map);// niveau
    void keyPressEvent(QKeyEvent *event);
    void updateScene();
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
    PacMan * Pacman;
    QGraphicsPixmapItem * PhantomRed;
    QGraphicsPixmapItem * PhantomPink;
    QGraphicsPixmapItem * PhantomBlue;
    QGraphicsPixmapItem * PhantomYellow;

    //Collectable
    QList<CollectableItem * > dots;
    QList<QGraphicsPixmapItem * > superDots;
    QGraphicsPixmapItem * fruit;

    //Game Info
    //QGraphicsTextItem * score;
    QGraphicsTextItem * level;
    //vies

    QTimer m_timer;

};

#endif // GAMESCENE_H
