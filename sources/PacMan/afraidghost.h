#ifndef AFRAIDGHOST_H
#define AFRAIDGHOST_H
#include "ghost.h"

class AfraidGhost : public Ghost
{
public:
    AfraidGhost();
    void nextIAMove(Graph *grap_control, Entity *e);
};

#endif // AFRAIDGHOST_H
