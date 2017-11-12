#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "graph.h"
#include "profil.h"
#include "vueprofile.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include "tilemap.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TileMap tm("../PacMan/levels/xml_level1.xml");

    Graph *g = new Graph(tm);

    int next_pos;
    next_pos = g->next_move(1,1,1,4);

    cout << "next move " << g->parse_move_c(next_pos) << " " << g->parse_move_l(next_pos) << endl;


    MainWindow w;
    w.show();




    //box_layout.addWidget(&widgetStack);
    //w.setLayout(&box_layout);


//    string fileName = "../PacMan/levels/levelTest.lvl";
//    int k = 2;
//    Graph* graph = new Graph(fileName.c_str());

//    Profil* p = new Profil("michel");

//    p->saveProfile("../PacMan/profil");


    return a.exec();
}
