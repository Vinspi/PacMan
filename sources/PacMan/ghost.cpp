#include "ghost.h"

Ghost::Ghost(QString skin) : Entity(skin)
{
    QPixmap pixmap("../PacMan/graphics_pacman/Affraid_ghost.png");

    setVitesse(1);
}



