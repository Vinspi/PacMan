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
#include "inky.h"
#include "pinky.h"
#include "deadghost.h"
#include "spawnblocclyde.h"
#include "spawnblocinky.h"
#include "spawnblocblinky.h"
#include "spawnblocpinky.h"
#include "hud.h"
#include <QGraphicsProxyWidget>
#include "mysterybloc.h"
#include "time.h"
#include <QGraphicsProxyWidget>
#include "gameview.h"
#include "profil.h"


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
    void setGameView(GameView *g);
    void reset();
    void useMysteryItem();
    void enableBerzerkMode();
    void setActiveProfil(Profil *profil);

public slots:
    void on_click_retour();
    void on_click_recommencer();
    void on_click_continuer();

private:
    GameView *gv;
    QGraphicsProxyWidget *pwrecommencer;
    QGraphicsProxyWidget *pwretour;
    QGraphicsProxyWidget *pwcontinuer;

    QGraphicsProxyWidget *pwgameover;
    QGraphicsProxyWidget *pwwin;

    QGraphicsProxyWidget *proxy_hud;

    Profil *activeProfile;

    const int NB_VIE_LEVEL = 3;
    bool mystery_box_spawn;
    void updateBerzerkMode();
    void updateTimerDebut();
    void spawnMysteryBloc();
    QTimer timerSpawnMysteryBloc;
    int score;
    TileManager * tm;
    TileMap tilemap;
    //RessourceManager ?
    //Background
    QGraphicsPixmapItem * background;
    QGraphicsPixmapItem * labyrinthe;

    //Movable
    PacMan * Pacman;
    Ghost * blinky;
    Ghost * clyde;
    Ghost * inky;
    Ghost * pinky;

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
    int next_move_inky;
    int next_move_pinky;
    int m_nb_dot;
    void gameOver();
    void win();
    bool berzerk_mode_active;
    bool berzerk_debuff_vitesse;
    HUD *hud;
    QPoint pacman_spawn_point;
    MysteryItem *m_mysteryItem;


    /* pour le timer de début de partie */

    QLabel *m_nombre_timer_deb;
    int compteur_timer_deb;
    QTimer *timer_debut;
    QGraphicsProxyWidget *tmp_prox;

    /*************************************/

};

#endif // GAMESCENE_H
