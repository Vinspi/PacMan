#ifndef DOTITEM_H
#define DOTITEM_H

#include "collectableitem.h"

class DotItem : public CollectableItem
{
public:
    enum { Type = UserType + 1};


    DotItem();
    int type() const;
   // QRectF boundingRect() const;
    QPainterPath shape() const;
};

#endif // DOTITEM_H
