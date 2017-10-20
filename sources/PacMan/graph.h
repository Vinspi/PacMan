#ifndef GRAPH_H
#define GRAPH_H
#include "sommet.h"
#include "const.h"

class Graph
{
public:
    Graph();

private:
   Sommet* matrice[W_WIDTH/T_SIZE][W_HEIGHT/T_SIZE];


};

#endif // GRAPH_H
