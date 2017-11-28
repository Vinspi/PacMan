#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QtXml>

class TileMap
{
public:
    TileMap();
    TileMap(QString filename);

    unsigned int width() const;
    unsigned int height() const;
    int tile(int r, int c) const;
    int tile_collectibles(int r,int c) const;
    int get_pos_pacman_init_row() const;
    int get_pos_pacman_init_col() const;

    int get_pos_blinky_init_row() const;
    int get_pos_blinky_init_col() const;

    int get_pos_inky_init_row() const;
    int get_pos_inky_init_col() const;

    int get_pos_pinky_init_row() const;
    int get_pos_pinky_init_col() const;

    int get_pos_clyde_init_row() const;
    int get_pos_clyde_init_col() const;
    QString getFileName();

private:
    QString file;
    unsigned int m_width;
    unsigned int m_height;
    QVector< QVector<int>> m_map;
    QVector< QVector<int>> m_map_collectibles;
    int pos_pacman_init_row;
    int pos_pacman_init_col;
    int pos_pinky_init_row;
    int pos_pinky_init_col;
    int pos_inky_init_row;
    int pos_inky_init_col;
    int pos_blinky_init_row;
    int pos_blinky_init_col;
    int pos_clyde_init_row;
    int pos_clyde_init_col;
};

#endif // TILEMAP_H
