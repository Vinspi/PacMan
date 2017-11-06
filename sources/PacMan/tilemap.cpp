#include "tilemap.h"
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <iostream>

using namespace std;

TileMap::TileMap(QString filename) : m_map()
{
    /* test XML */
    /* ouverture du fichier */
    QDomDocument dom(filename);
    QFile xml_level("../PacMan/levels/xml_level.xml");

    if(!xml_level.open(QIODevice::ReadOnly)){
        qDebug("cannot open file");
        return;
    }
    if(!dom.setContent(&xml_level)){
        xml_level.close();
        qDebug("cannot bind file");
        return;
    }

    /* on recupere la taille de la map */


    QDomNodeList node_list = dom.elementsByTagName("tilemap-width");
    QDomNode w_node = node_list.at(0);
    m_width = w_node.toElement().attribute("value","undefined").toInt();
    m_map.resize(m_width);

    node_list = dom.elementsByTagName("tilemap-height");
    QDomNode h_node = node_list.at(0);
    m_height = h_node.toElement().attribute("value","undefined").toInt();
    for(int i=0;i<m_width;i++){
        m_map[i].resize(m_height);
    }
    /* on recherche l'element qui nous interresse */

    node_list = dom.elementsByTagName("layer");
    QDomNode background_node;
    for(int i=0;i<node_list.size();i++){
        if(node_list.at(i).toElement().attribute("id","undefined") == "background"){
            background_node = node_list.at(i);
        }
    }


    QDomNode row = background_node.firstChild();
    QDomNode tile = row.firstChild();
    cout << row.toElement().tagName().toStdString() << endl;
    /* on parcours tout le tag <layer id=background> */
    /* pour chaque row */
    while(!row.isNull()){
        /* pour chaque tile */
        while(!tile.isNull()){

//            cout << tile.toElement().tagName().toStdString() << " ";
//            cout << tile.toElement().attribute("row","undefined").toStdString() << " ";
//            cout << tile.toElement().attribute("col","undefined").toStdString() << " ";
//            cout << tile.toElement().attribute("value","undefined").toStdString() << endl;
            m_map[tile.toElement().attribute("col").toInt()][tile.toElement().attribute("row").toInt()] = tile.toElement().attribute("value").toInt();

            tile = tile.nextSibling();
        }
        row = row.nextSibling();
        tile = row.firstChild();
    }

    xml_level.close();
    /* --------------------------------------------------------*/
//    QFile level_file(filename);
//    if(level_file.open(QIODevice::ReadOnly))
//    {
//        QTextStream in(&level_file);
//        int width = 0, height = 0;
//        int num = 0;

//        in >> width;
//        m_width = width;

//        in >> height;
//        m_height = height;

//        m_map.resize(height);

//        for(int r = 0; r < height; r++)//line
//        {
//            m_map[r].resize(width);

//            for(int c = 0; c < width; c++)
//            {
//                in >> num;
//                m_map[r][c] = num;
//            }
//        }
//        level_file.close();
//    }
//    else
//    {
//        qDebug("cannot open file");
//    }
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
