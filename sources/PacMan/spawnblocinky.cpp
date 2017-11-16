#include "spawnblocinky.h"

SpawnBlocInky::SpawnBlocInky() : BlocItem()
{
    setPixmap(QPixmap("../PacMan/graphics_pacman/tileset.png").copy(5*32,0,32,32));
}
