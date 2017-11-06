#include "collectableitem.h"

CollectableItem::CollectableItem(unsigned int a) : QGraphicsPixmapItem(), score(a)
{
}

unsigned int CollectableItem::value() const
{
    return score;
}
