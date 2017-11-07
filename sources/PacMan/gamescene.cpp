#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>


GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), superDots()
{
    this->tm = tm;
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
    //labyrinthe->setOffset(16, 16);

    CollectableItem *dot;

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






    //Pacman = addPixmap(QPixmap("../pacmanmoves").copy(0,28,14,14));
    //Pacman->setOffset(21, 198);
}

void GameScene::checkCollisions()
{
    QList<QGraphicsItem *> list = collidingItems(Pacman);

    for(int i = 0; i < list.size(); i++)
    {
        if(DotItem *d = qgraphicsitem_cast<DotItem *>(list.at(i)))
        {
            score += d->value();
            removeItem(d);
            delete d;
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
            Pacman->setOffset(Pacman->offset() + QPointF(8, 0));
            break;
        case Qt::Key_Left:
            Pacman->setOffset(Pacman->offset() + QPointF(-8, 0));
            break;
        case Qt::Key_Down:
            Pacman->setOffset(Pacman->offset() + QPointF(0, 8));
            break;
        case Qt::Key_Up:
            Pacman->setOffset(Pacman->offset() + QPointF(0, -8));
            break;
        default:
            break;
    }

    checkCollisions();
}
