#include "tilemanager.h"
#include <QPainter>

TileManager::TileManager(QString filename) : tiles()
{
    QPixmap tileset(filename);
    int width, height;
    width = tileset.width();
    height = tileset.height();

    int tilesize = 32;

    for(int h = 0; h < height / tilesize; h++)
    {
        for(int w = 0; w < width / tilesize; w++)
        {
            QRect rect(w * tilesize, h * tilesize, tilesize, tilesize);
            QPixmap tile = tileset.copy(rect);
            tiles.append(tile);
        }
    }

}

QPixmap TileManager::drawPixmapLevel()
{
    //Obtenir la taille du level en pixel
    QPixmap level(600,800);
    QPainter painter(&level);
    //Lire le fichier ou une matrice pour peindre le level
    //painter.drawPixmap(...)
    return level;
}

QVector<QPixmap> TileManager::Tiles()
{
    return tiles;
}
