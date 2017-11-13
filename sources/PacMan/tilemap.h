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
    int tile_collectibles(int r,int c) const;
    int get_pos_pacman_init_row();
    int get_pos_pacman_init_col();
    //void setTile(int tiles[][], int w, int h);

private:
    unsigned int m_width;
    unsigned int m_height;
    QVector< QVector<int>> m_map;
    QVector< QVector<int>> m_map_collectibles;
    int pos_pacman_init_row;
    int pos_pacman_init_col;
};

#endif // TILEMAP_H
