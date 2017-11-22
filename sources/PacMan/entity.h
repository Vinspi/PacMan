#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsPixmapItem>
#include <QVector>
#include "const.h"
#include <QPainter>
#include <QDebug>



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
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    QPoint current_tile_pos();
    void setMode(int mode);
    void nextTile();
    void setLastPos(QPointF lastpos);
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);

private:
    int m_direction;
    int m_vitesse;
    int m_vitesse_iterator;
    int m_frame;
    int m_last_frame;
    int m_last_direction;
    QPointF m_last_position;


protected:
    /* contain sprites for animation */
    QVector<QPixmap> moveUp;
    QVector<QPixmap> moveDown;
    QVector<QPixmap> moveLeft;
    QVector<QPixmap> moveRight;
    int m_max_frame;
    int m_mode;

};

#endif // ENTITY_H
