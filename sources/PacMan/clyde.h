#ifndef CLYDE_H
#define CLYDE_H
#include "entity.h"
#include "ghost.h"


class Clyde : public Ghost
{
public:
    Clyde();
    void nextIAMove(Graph *graph_control,Entity *e);

};

#endif // CLYDE_H
