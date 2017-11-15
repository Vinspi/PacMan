#include "blinky.h"

Blinky::Blinky() : Ghost("../PacMan/graphics_pacman/Blinky.png")
{
    setVitesse(4);
}

void Blinky::nextIAMove(Graph *graph_control,Entity *e){
    QPoint pos_blinky = current_tile_pos();
    QPoint pos_pacman = e->current_tile_pos();
    int next_move_blinky;

    int next_blinky_move = graph_control->next_move(pos_blinky.x(),pos_blinky.y(),pos_pacman.x(),pos_pacman.y());

    int next_move_c_blinky = graph_control->parse_move_c(next_blinky_move);
    int next_move_l_blinky = graph_control->parse_move_l(next_blinky_move);

    /* la direction sera LEFT */
    if(pos_blinky.x() > next_move_c_blinky){
        next_move_blinky = LEFT;

    }
    /* la direction sera RIGHT */
    if(pos_blinky.x() < next_move_c_blinky){
        next_move_blinky = RIGHT;

    }
    /* la direction sera UP */
    if(pos_blinky.y() > next_move_l_blinky){
        next_move_blinky = UP;

    }
    /* la direction sera DOWN */
    if(pos_blinky.y() < next_move_l_blinky){
        next_move_blinky = DOWN;
    }

    setDirection(next_move_blinky);
}
