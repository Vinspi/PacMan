#ifndef FLASHAFRAIDGHOST_H
#define FLASHAFRAIDGHOST_H
#include "ghost.h"

class FlashAfraidGhost : public Ghost
{
public:
    FlashAfraidGhost();
    void nextIAMove(Graph *graph_control,Entity *e);
};

#endif // FLASHAFRAIDGHOST_H
