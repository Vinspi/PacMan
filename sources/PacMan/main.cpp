#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    string fileName = "../PacMan/levels/levelTest.lvl";
    int k = 2;
    Graph* graph = new Graph(fileName.c_str());



    return a.exec();
}
