#include "gameview.h"
#include <QPainter>

GameView::GameView(QWidget *parent) : QWidget(parent)
{
    labyrinthe = new QLabel(this);
    labyrinthe->setPixmap(QPixmap());
}
