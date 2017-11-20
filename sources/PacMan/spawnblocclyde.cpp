#include "spawnblocclyde.h"

SpawnBlocClyde::SpawnBlocClyde() : BlocItem()
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/tileset.png").copy(2*32,0,32,32));
}


