#include "deadghost.h"

DeadGhost::DeadGhost() : Ghost("../PacMan/graphics_pacman/Dead_ghost.png")
{
    setVitesse(6);
}

void DeadGhost::nextIAMove(Graph *graph_control, Entity *e){
    QPoint pos = current_tile_pos();

    int next_move = graph_control->next_move(pos.x(),pos.y(),m_spawn_point.x(),m_spawn_point.y());

    int next_move_c = graph_control->parse_move_c(next_move);
    int next_move_l = graph_control->parse_move_l(next_move);

    int next_ghost_move;

    /* la direction sera LEFT */
    if(pos.x() > next_move_c){
        next_ghost_move = LEFT;

    }
    /* la direction sera RIGHT */
    if(pos.x() < next_move_c){
        next_ghost_move = RIGHT;

    }
    /* la direction sera UP */
    if(pos.y() > next_move_l){
        next_ghost_move = UP;

    }
    /* la direction sera DOWN */
    if(pos.y() < next_move_l){
        next_ghost_move = DOWN;
    }

    //qDebug() << "next dir : " << next_ghost_move;

    setDirection(next_ghost_move);
}
