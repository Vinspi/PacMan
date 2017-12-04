#include "gameview.h"
#include <QPainter>
#include <QStackedWidget>

GameView::GameView(QGraphicsScene *parent) : QGraphicsView(parent)
{

}

void GameView::setWid(){
    ((QStackedWidget*) this->parent())->setCurrentIndex(0); 
}
