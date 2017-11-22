#include "mysterybloc.h"

MysteryBloc::MysteryBloc() : CollectableItem(50)
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/mystery_box.png").copy(0,0,32,32));
    srand(NULL);
    SuperDotItem *super = new SuperDotItem();
    addMysteryItem(super);
}

void MysteryBloc::addMysteryItem(MysteryItem* item){
    items.append(item);
}

MysteryItem* MysteryBloc::randomItem(){
    if(items.size() > 0){
        int rand_i = rand()%(items.size());
        return items.at(rand_i)->copy();
    }
    else{
        qDebug() << "attention mysterybloc est vide !";
        return nullptr;
    }
}
