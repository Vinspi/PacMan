#ifndef MURITEM_H
#define MURITEM_H
#include "blocitem.h"

class MurItem : public BlocItem
{
public:
    MurItem();
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
};

#endif // MURITEM_H
