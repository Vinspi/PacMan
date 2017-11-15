#include "clyde.h"

Clyde::Clyde() : Ghost("../PacMan/graphics_pacman/Clyde.png")
{
    setVitesse(5);
}

void Clyde::nextIAMove(Graph *graph_control,Entity *e){
    QPoint pos_clyde = current_tile_pos();
    int next_move_clyde = graph_control->next_random_move(pos_clyde.x(),pos_clyde.y(),direction());

    Ghost::setDirection(next_move_clyde);
}
