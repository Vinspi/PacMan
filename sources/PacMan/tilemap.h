#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QtXml>

class TileMap
{
public:
    TileMap(QString filename);

    unsigned int width() const;
    unsigned int height() const;
    int tile(int r, int c) const;

private:
    unsigned int m_width;
    unsigned int m_height;
    QVector< QVector<int>> m_map;
};

#endif // TILEMAP_H
