#include "muritem.h"

MurItem::MurItem() : BlocItem()
{

}

void MurItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget){
    painter->drawRect(QRect(0,0,32,32));
}


QPainterPath MurItem::shape() const {
    QPainterPath path;
    path.addRect(QRect(0,0,32,32));
    return path;
}

QRectF MurItem::boundingRect() const {
    return QRectF(0,0,32,32);
}
