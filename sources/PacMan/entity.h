#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsPixmapItem>
#include <QVector>
#include "const.h"


class Entity: public QGraphicsPixmapItem
{
public:
    Entity();
    Entity(QString skin);
    void avance();
    int direction();
    int vitesse();
    void setDirection(int dir);

private:

    /* contain sprites for animation */
    QVector<QPixmap> moveUp;
    QVector<QPixmap> moveDown;
    QVector<QPixmap> moveLeft;
    QVector<QPixmap> moveRight;
    int m_direction;
    int m_vitesse;

};

#endif // ENTITY_H
