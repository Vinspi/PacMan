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
#include "blocitem.h"
#include "muritem.h"
#include "graph.h"
#include "blinky.h"
#include "graph.h"
#include "clyde.h"


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
    int checkCollisions();
    int checkCollisionsBlinky();

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
    Blinky * blinky;
    Clyde * clyde;

    QGraphicsPixmapItem * PhantomRed;
    QGraphicsPixmapItem * PhantomPink;
    QGraphicsPixmapItem * PhantomBlue;
    QGraphicsPixmapItem * PhantomYellow;

    //Collectable
    QList<CollectableItem * > dots;
    QList<QGraphicsPixmapItem * > blocs;
    QGraphicsPixmapItem * fruit;

    //Game Info
    //QGraphicsTextItem * score;
    QGraphicsTextItem * level;
    //vies

    Graph* graph_control;
    QTimer m_timer;
    int next_move;
    int next_move_blinky;
    int m_nb_dot;
    void gameOver();
    void win();

};

#endif // GAMESCENE_H
