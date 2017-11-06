#include "tilemap.h"
#include <QFile>
#include <QTextStream>
#include <stdio.h>

TileMap::TileMap(QString filename) : m_map()
{
    QFile level_file(filename);
    if(level_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&level_file);
        int width = 0, height = 0;
        int num = 0;

        in >> width;
        m_width = width;

        in >> height;
        m_height = height;

        m_map.resize(height);

        for(int r = 0; r < height; r++)//line
        {
            m_map[r].resize(width);

            for(int c = 0; c < width; c++)
            {
                in >> num;
                m_map[r][c] = num;
            }
        }
        level_file.close();
    }
    else
    {
        qDebug("cannot open file");
    }
}

unsigned int TileMap::width() const
{
    return m_width;
}

unsigned int TileMap::height() const
{
    return m_height;
}

int TileMap::tile(int r, int c) const
{
    return m_map[r][c];
}
