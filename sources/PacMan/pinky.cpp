#include "pinky.h"

Pinky::Pinky() : Ghost("../PacMan/graphics_pacman/Pinky.png")
{
    setVitesse(5);
}

void Pinky::nextIAMove(Graph *graph_control, Entity *e){
    QPoint pos_ghost = current_tile_pos();
    int next_move_ghost = graph_control->next_random_move(pos_ghost.x(),pos_ghost.y(),direction());

    setDirection(next_move_ghost);
}
