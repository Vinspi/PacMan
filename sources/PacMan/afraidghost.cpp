#include "afraidghost.h"

AfraidGhost::AfraidGhost() : Ghost("../PacMan/graphics_pacman/Afraid_ghost.png")
{
    setVitesse(2);
}

void AfraidGhost::nextIAMove(Graph *graph_control, Entity *e) {
    QPoint pos_ghost = current_tile_pos();
    int next_move_ghost = graph_control->next_random_move(pos_ghost.x(),pos_ghost.y(),direction());

    setDirection(next_move_ghost);

}
