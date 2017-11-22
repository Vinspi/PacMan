#include "collectableitem.h"

CollectableItem::CollectableItem(unsigned int a) : BlocItem(), score(a)
{
}

unsigned int CollectableItem::value() const
{
    return score;
}

