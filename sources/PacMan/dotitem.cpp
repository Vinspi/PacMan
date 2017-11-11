#include "dotitem.h"

DotItem::DotItem() : CollectableItem(10)
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/gumgum.png").copy(0,0,32,32));
}

int DotItem::type() const
{
    return Type;
}

QPainterPath DotItem::shape() const  {
    QPainterPath path;
    path.addRect(10,10,10,10);
    return path;
}


//QRectF DotItem::boundingRect() const{
//    return QRectF(-30,-30,60,60);
//}
