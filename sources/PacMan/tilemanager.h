#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>
#include <QVector>
#include <QString>

class TileManager
{
    public:
        TileManager(QString filename);
        QVector<QPixmap> Tiles();

        QPixmap drawPixmapLevel();

    private:
        QVector<QPixmap> tiles;
        //Pointeur du pixmap du tileset au cas ou
};

#endif // TILESET_H
