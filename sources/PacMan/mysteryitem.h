#ifndef MYSTERYITEM_H
#define MYSTERYITEM_H
#include <QGraphicsPixmapItem>

class MysteryItem : public QGraphicsPixmapItem
{
public:
    MysteryItem();
    virtual MysteryItem* copy();
};

#endif // MYSTERYITEM_H
