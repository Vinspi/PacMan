#ifndef MURITEM_H
#define MURITEM_H
#include "blocitem.h"

class MurItem : public BlocItem
{
public:
    MurItem();
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);
};

#endif // MURITEM_H
