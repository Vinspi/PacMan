#include "tilemanager.h"
#include <QPainter>
//#include "levels.h"

TileManager::TileManager(QString filename) : tiles()
{
    QPixmap tileset(filename);
    int width, height;
    width = tileset.width();
    height = tileset.height();

    int tilesize = T_SIZE;
    //tiles.append(QPixmap(0,0));//Tile numéroté à partir de 1,on ajoute un pixmap vide en indice 0

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




QPixmap TileManager::drawTileMap(TileMap &map)
{
    int tilesize = T_SIZE;
    int w = map.width();
    int h = map.height();

    QPixmap level(w * tilesize, h * tilesize);
    QPainter painter(&level);

    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            painter.drawPixmap(c * tilesize, r * tilesize, tiles[map.tile(r, c)]);
        }
    }

    return level;
}



QVector<QPixmap> TileManager::Tiles()
{
    return tiles;
}
