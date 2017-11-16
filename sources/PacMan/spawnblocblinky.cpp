#include "spawnblocblinky.h"

SpawnBlocBlinky::SpawnBlocBlinky() : BlocItem()
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/tileset.png").copy(3*32,0,32,32));
}
