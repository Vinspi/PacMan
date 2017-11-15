#ifndef PINKY_H
#define PINKY_H

#include "entity.h"
#include "ghost.h"

class Pinky : public Ghost
{
public:
    Pinky();
    virtual void nextIAMove(Graph *graph_control, Entity *e);
};

#endif // PINKY_H
