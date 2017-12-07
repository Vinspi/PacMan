#include "testmodulegraph.h"
#include "tilemap.h"
#include <QDebug>

/* dans cette classe nous ferons le test des fonctionnalitées qu'offre le graphe de contrôle */
TestModuleGraph::TestModuleGraph()
{
    /* on commence par créer un graphe et une tilemap avec le fichier de test */
    TileMap t("./xml_levelTest.xml");
    Graph *g = new Graph(t);

    /* le graphe de contrôle est donc celui obtenu à partir du fichier de test */

    /* test boite noire fonction next_ambush_move() (IA de Inky) */

    /* ici le fantôme se trouve en (3,22) et le pacman se trouve en (2,1) et se dirige vers la droite */
    int move1 = g->next_ambush_move(22,3,2,1,RIGHT);

    int move1_c = g->parse_move_c(move1);
    int move1_l = g->parse_move_l(move1);


    /* ici le fantôme se trouve en (3,22) et le pacman se trouve en (2,1) et se dirige vers la GAUCHE */
    int move2 = g->next_ambush_move(22,3,2,1,LEFT);

    int move2_c = g->parse_move_c(move2);
    int move2_l = g->parse_move_l(move2);

    /* ici le fantôme se trouve en (22,20) et le pacman se trouve en (1,2) et se dirige vers le bas */
    int move3 = g->next_ambush_move(22,20,1,2,DOWN);

    int move3_c = g->parse_move_c(move3);
    int move3_l = g->parse_move_l(move3);

    /* ici le fantôme se trouve en (22,1) et le pacman se trouve en (1,2) et se dirige vers le haut */
    int move4 = g->next_ambush_move(22,1,1,2,UP);

    int move4_c = g->parse_move_c(move4);
    int move4_l = g->parse_move_l(move4);

    /* le point d'embuscade du fantôme se trouve en (23,1), le fantôme se trouvant en (23,3) le
     * prochain mouvement de celui-ci devrait se trouver en (23,2).
     * /

     /* test ambush */
    qDebug() << "test 1";
    assertGraph((move1_c == 22) && (move1_l == 2));

    /* le point d'embuscade du fantôme se trouve en (1,1), le fantôme se trouvant en (23,3) le
     * prochain mouvement de celui-ci devrait se trouver en (23,2).
     * /

     /* test ambush */
    qDebug() << "test 2";
    assertGraph((move2_c == 22) && (move2_l == 2));

    /* le point d'embuscade du fantôme se trouve en (1,22), le fantôme se trouvant en (22,20) le
     * prochain mouvement de celui-ci devrait se trouver en (22,21).
     * /

     /* test ambush */
    qDebug() << "test3";
    assertGraph((move3_c == 22) && (move3_l == 21));

    /* le point d'embuscade du fantôme se trouve en (1,1), le fantôme se trouvant en (22,1) le
     * prochain mouvement de celui-ci devrait se trouver en (21,1).
     * /

     /* test ambush */
    qDebug() << "test4";
    assertGraph((move4_c == 21) && (move4_l == 1));

    /**** fin de test de la fonction ambush *****/

    /*** test de la fonction next move ***/

    /*** ceci est in dijkstra simple ***/

    int move5 = g->next_move(1,1,22,3);

    int move5_c = g->parse_move_c(move5);
    int move5_l = g->parse_move_l(move5);

    /* on cherche le prochain movement pour aller de (1,1) à (22,3) ce qui est donc (2,1) dans notre fichier de test */

    assertGraph((move5_c == 2)&&(move5_l == 1));

    /* fin du test */

}

void TestModuleGraph::assertGraph(int assert){
    if(assert){
        qDebug() << "assertion verifié";
    }
    else{
        qDebug() << "assertion fausse";
        exit(1);
    }
}
