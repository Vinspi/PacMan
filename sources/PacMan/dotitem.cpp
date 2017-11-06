#include "dotitem.h"

DotItem::DotItem() : CollectableItem(10)
{
    setPixmap(QPixmap("../gums_8px").copy(0,0,8,8));
}

int DotItem::type() const
{
    return Type;
}
