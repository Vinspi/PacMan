#include "inky.h"

Inky::Inky() : Ghost("../PacMan/graphics_pacman/Inky.png")
{
    setVitesse(4);
}

void Inky::nextIAMove(Graph *graph_control,Entity *e){
    QPoint pos_inky = current_tile_pos();
    QPoint pos_pacman = e->current_tile_pos();
    int next_move_inky;

    int next_inky_move = graph_control->next_ambush_move(pos_inky.x(),pos_inky.y(),pos_pacman.x(),pos_pacman.y(),e->direction());

    int next_move_c_inky = graph_control->parse_move_c(next_inky_move);
    int next_move_l_inky = graph_control->parse_move_l(next_inky_move);



    /* la direction sera LEFT */
    if(pos_inky.x() > next_move_c_inky){
        next_move_inky = LEFT;

    }
    /* la direction sera RIGHT */
    if(pos_inky.x() < next_move_c_inky){
        next_move_inky = RIGHT;

    }
    /* la direction sera UP */
    if(pos_inky.y() > next_move_l_inky){
        next_move_inky = UP;

    }
    /* la direction sera DOWN */
    if(pos_inky.y() < next_move_l_inky){
        next_move_inky = DOWN;

    }



    setDirection(next_move_inky);
}
