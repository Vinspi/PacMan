#ifndef GHOST_H
#define GHOST_H
#include "entity.h"
#include <QPixmap>
#include "graph.h"


class Ghost : public Entity
{
public:
    Ghost();
    Ghost(QString skin);
    //virtual void nextIAMove(Graph *graph_control);


private:


};

#endif // GHOST_H
