#include "spawnblocpinky.h"

SpawnBlocPinky::SpawnBlocPinky() : BlocItem()
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/tileset.png").copy(4*32,0,32,32));
}
