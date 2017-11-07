#include "dotitem.h"

DotItem::DotItem() : CollectableItem(10)
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/gumgum.png").copy(0,0,32,32));
}

int DotItem::type() const
{
    return Type;
}
