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

    TileMap tm("../PacMan/levels/xml_level2.xml");

    Graph *g = new Graph(tm);

    g->affiche();
    g->affiche_routage();
    //int next_move = g->next_move(2,2,1,1);

    //cout << g->parse_move_c(next_move) << " " << g->parse_move_l(next_move) << endl;

    QApplication a(argc, argv);
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
