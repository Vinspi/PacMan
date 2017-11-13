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
#include "afraidghost.h"
#include "flashafraidghost.h"


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
    int checkCollisionsGhost(Ghost *ghost);

public slots:

private:
    void updateBerzerkMode();
    int score;
    TileManager * tm;
    //RessourceManager ?
    //Background
    QGraphicsPixmapItem * background;
    QGraphicsPixmapItem * labyrinthe;

    //Movable
    PacMan * Pacman;
    Ghost * blinky;
    Ghost * clyde;

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
    QTimer m_timer_berzerk_mode;
    int m_time_elapsed_berzerk_mode;
    int next_move;
    int next_move_blinky;
    int next_move_clyde;
    int m_nb_dot;
    void gameOver();
    void win();

};

#endif // GAMESCENE_H
