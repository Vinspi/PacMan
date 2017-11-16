#ifndef DEADGHOST_H
#define DEADGHOST_H
#include "ghost.h"

class DeadGhost : public Ghost
{
public:
    DeadGhost();
    virtual void nextIAMove(Graph *graph_control, Entity *e);
};

#endif // DEADGHOST_H
