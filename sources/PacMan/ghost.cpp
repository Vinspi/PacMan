#include "ghost.h"

Ghost::Ghost(QString skin) : Entity(skin)
{
    QPixmap pixmap("../PacMan/graphics_pacman/Affraid_ghost.png");

    setVitesse(1);
}


void Ghost::nextIAMove(Graph *graph_control, Entity *e) {
    QPoint pos_ghost = current_tile_pos();
    int next_move_ghost = graph_control->next_random_move(pos_ghost.x(),pos_ghost.y(),direction());

    setDirection(next_move_ghost);

}
