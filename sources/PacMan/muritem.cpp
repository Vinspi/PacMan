#include "muritem.h"

MurItem::MurItem() : BlocItem()
{

}


QPainterPath MurItem::shape() const {
    QPainterPath path;
    path.addRect(QRect(0,0,32,32));
    return path;
}

QRectF MurItem::boundingRect() const {
    return QRectF(0,0,32,32);
}
