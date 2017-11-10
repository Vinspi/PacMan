#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>
#include <QVector>
#include <QString>
#include "tilemap.h"
#include "const.h"

class TileManager
{
public:
    TileManager(QString filename);
    QVector<QPixmap> Tiles();


    QPixmap drawTileMap(TileMap &map);

private:
    QVector<QPixmap> tiles;

};

#endif // TILESET_H
