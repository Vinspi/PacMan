#ifndef COLLECTABLEITEM_H
#define COLLECTABLEITEM_H

#include <QGraphicsPixmapItem>

class CollectableItem : public QGraphicsPixmapItem
{
public:
    CollectableItem(unsigned int a);
    unsigned int value() const;


protected:
    unsigned int score;
};

#endif // COLLECTABLEITEM_H
