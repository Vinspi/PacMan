#ifndef SUPERDOTITEM_H
#define SUPERDOTITEM_H

#include "collectableitem.h"

class SuperDotItem : public CollectableItem
{
public:
    enum { Type = UserType + 2};

    SuperDotItem();
    int type() const;
};

#endif // SUPERDOTITEM_H
