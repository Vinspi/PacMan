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
    virtual void nextIAMove(Graph *graph_control, Entity *e);
    void setSpawnPoint(QPoint spawn_point);

    QPoint spawnPoint();

protected:
    QPoint m_spawn_point;

};

#endif // GHOST_H
