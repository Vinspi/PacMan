#ifndef INKY_H
#define INKY_H

#include "entity.h"
#include "ghost.h"

class Inky : public Ghost
{
public:
    Inky();
    virtual void nextIAMove(Graph *graph_control, Entity *e);
};

#endif // INKY_H
