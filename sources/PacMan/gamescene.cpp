#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>
#include <iostream>

using namespace std;

GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), m_timer()
{
    this->tm = tm;
    m_timer.setInterval(10);

    connect(&m_timer,&QTimer::timeout,this,&GameScene::updateScene);
    m_timer.start();
}

void GameScene::updateScene(){
    Pacman->avance();
    checkCollisions();

    this->update();
}

void GameScene::init(TileMap &map)
{
    clear();
    score = 0;
    setSceneRect(0, 0, map.width() * T_SIZE, map.height() * T_SIZE);
    QPixmap bg(map.width() * T_SIZE, map.height() * T_SIZE);
    bg.fill(Qt::black);
    background = addPixmap(bg);
    labyrinthe = addPixmap(tm->drawTileMap(map));
    Pacman = new PacMan();

    //labyrinthe->setOffset(16, 16);

    CollectableItem *dot;
    BlocItem *mur;

    for(int i=0;i<map.width();i++){
        for(int j=0;j<map.height();j++){
            /* si c'est un bloc */
            if(map.tile(i,j) == 0){
                mur = new MurItem();
                mur->setPos(j*32,i*32);
                addItem(mur);
            }
        }
    }

    for(int i=0;i<map.width();i++){
        for(int j=0;j<map.height();j++){
            if(map.tile_collectibles(i,j) == 1){
                dot = new DotItem();
                dot->setPos(j*32,i*32);
                dots.append(dot);
                addItem(dot);
            }
            if(map.tile_collectibles(i,j) == 2){
                dot = new SuperDotItem();
                dot->setPos(j*32,i*32);
                dots.append(dot);
                addItem(dot);
            }
        }
    }

    qDebug() << map.get_pos_pacman_init_col();
    Pacman->setPos(map.get_pos_pacman_init_col()*T_SIZE,map.get_pos_pacman_init_row()*T_SIZE);
    addItem(Pacman);



    //Pacman = addPixmap(QPixmap("../pacmanmoves").copy(0,28,14,14));
    //Pacman->setOffset(21, 198);
}

void GameScene::checkCollisions()
{
    QList<QGraphicsItem *> list = collidingItems(Pacman);

    for(int i = 0; i < list.size(); i++)
    {
        if(CollectableItem *d = dynamic_cast<CollectableItem *>(list.at(i)))
        {
            removeItem(list.at(i));
            delete list.at(i);
            score += d->value();
            qDebug() << "score" << score << endl;
        }
        else if(BlocItem *b = dynamic_cast<BlocItem *>(list.at(i))){
            Pacman->annule_deplacement();
            qDebug() << "deplacement annulé" << endl;
        }
    }

}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch(event->key())
    {
        case Qt::Key_Right:
            Pacman->setDirection(RIGHT);
            break;
        case Qt::Key_Left:
            Pacman->setDirection(LEFT);
            break;
        case Qt::Key_Down:
            Pacman->setDirection(DOWN);
            break;
        case Qt::Key_Up:
            Pacman->setDirection(UP);
            break;
        default:
            break;
    }

    checkCollisions();
}
