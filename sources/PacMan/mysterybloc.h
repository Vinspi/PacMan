#ifndef MYSTERYBLOC_H
#define MYSTERYBLOC_H
#include "collectableitem.h"
#include <random>
#include "mysteryitem.h"
#include "superdotitem.h"
#include "time.h"
#include <QDebug>

class MysteryBloc : public CollectableItem
{
public:
    MysteryBloc();
    MysteryItem* randomItem();
    void addMysteryItem(MysteryItem *item);
private:
    QList<MysteryItem *> items;
};

#endif // MYSTERYBLOC_H
