#ifndef SUPERDOTITEM_H
#define SUPERDOTITEM_H

#include "collectableitem.h"
#include "mysteryitem.h"

class SuperDotItem : public CollectableItem, public MysteryItem
{
public:
    enum { Type = UserType + 2};

    SuperDotItem();
    int type() const;
    virtual MysteryItem* copy();
};

#endif // SUPERDOTITEM_H
