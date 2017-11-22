#ifndef COLLECTABLEITEM_H
#define COLLECTABLEITEM_H

#include "blocitem.h"

class CollectableItem : public BlocItem
{
public:
    CollectableItem(unsigned int a);
    unsigned int value() const;


protected:
    unsigned int score;
};

#endif // COLLECTABLEITEM_H
