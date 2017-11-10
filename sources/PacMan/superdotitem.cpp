#include "superdotitem.h"

SuperDotItem::SuperDotItem(): CollectableItem(100)
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/supergumgum.png").copy(0,0,32,32));
}


int SuperDotItem::type() const
{
    return Type;
}
