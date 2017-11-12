#ifndef GRAPH_H
#define GRAPH_H
#include "const.h"
#include <iostream>
#include "tilemap.h"
#include <climits>
#include <QList>

using namespace std;

class Graph
{
public:
    Graph(TileMap m);
    int arc(int x1, int y1, int x2, int y2);
    int next_move(int c1, int l1, int c2, int l2);
    int parse_move_c(int move);
    int parse_move_l(int move);

private:
   int a[24*24][24*24]; /* maybe use a non static element like QVector instead ?? */
   int routage[24*24][24*24];
   void initMatrice();
   void setArc(int l1, int c1, int l2, int c2);
   void affiche() const;
   void Dijkstra(int l1, int c1, int prec[]) const;
   int findMin(QList<int> *front, int dist[]) const;
   int m_map_width;
   int m_map_height;
   void calcule_routage();



};

#endif // GRAPH_H
