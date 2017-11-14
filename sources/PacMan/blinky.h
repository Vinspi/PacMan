#ifndef BLINKY_H
#define BLINKY_H

#include "entity.h"
#include "ghost.h"

class Blinky : public Ghost
{
public:
    Blinky();
    void nextIAMove(Graph *graph_control, Entity *e);
};

#endif // BLINKY_H
