#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsPixmapItem>
#include <QVector>
#include "const.h"
#include <QPainter>



class Entity: public QGraphicsPixmapItem
{
public:
    Entity();
    Entity(QString skin);
    void avance();
    void annule_deplacement();
    int direction();
    int vitesse();
    void setDirection(int dir);
    void setVitesse(int v);
    //QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);

private:

    /* contain sprites for animation */
    QVector<QPixmap> moveUp;
    QVector<QPixmap> moveDown;
    QVector<QPixmap> moveLeft;
    QVector<QPixmap> moveRight;
    int m_direction;
    int m_vitesse;
    int m_frame;
    int m_max_frame;
    int m_last_frame;

};

#endif // ENTITY_H
