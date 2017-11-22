#include "mysteryitem.h"

MysteryItem::MysteryItem() : QGraphicsPixmapItem()
{

}

MysteryItem* MysteryItem::copy(){
    return new MysteryItem;
}
