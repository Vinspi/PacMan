#include "graph.h"


using namespace std;

Graph::Graph(TileMap map)
{
    srand(NULL);
    m_map_width = map.width();
    m_map_height = map.height();
    initMatrice();

    for(int c=1;c<map.width()-1;c++){
        for(int l=1;l<map.height()-1;l++){
            /* voisin en bas */
            if(map.tile(c,l) == 1 && map.tile(c,l+1) == 1){

                setArc(c,l,c,l+1);
                setArc(c,l+1,c,l);
            }
            /* voisin a droite */
            if(map.tile(c,l) == 1&& map.tile(c+1,l) == 1){

                setArc(c,l,c+1,l);
                setArc(c+1,l,c,l);
            }
            /* les autres cas sont complémentaires (enfin j'espère) */
        }
    }

    int prec[m_map_width*m_map_width];

    //affiche();

    calcule_routage();



}

int Graph::next_ambush_move(int c, int l, int c_pacman, int l_pacman, int dir_pacman){

    /* trouver le prochain endroit propice à une embuscade */

    int c_tempo = c_pacman, l_tempo = l_pacman;

    switch (dir_pacman) {
    case UP:
        /* si le pacman se dirige vers le haut on va chercher le prochain carrefour dans cette direction */
        while (!arc(c_tempo,l_tempo,c_tempo-1,l_tempo) && !arc(c_tempo,l_tempo,c_tempo+1,l_tempo)) {
            /* on recule donc d'une ligne */
            l_tempo--;
        }
        /* ici la pos (c_tempo,l_tempo) est propice à l'embuscade */
        return next_move(c,l,c_tempo,l_tempo);

    case DOWN:
        /* si le pacman se dirige vers le bas on va chercher le prochain carrefour dans cette direction */
        while (!arc(c_tempo,l_tempo,c_tempo-1,l_tempo) && !arc(c_tempo,l_tempo,c_tempo+1,l_tempo)) {
            /* on avance donc d'une ligne */
            l_tempo++;
        }
        /* ici la pos (c_tempo,l_tempo) est propice à l'embuscade */
        return next_move(c,l,c_tempo,l_tempo);

    case RIGHT:
        /* si le pacman se dirige vers la droite on va chercher le prochain carrefour dans cette direction */
        while (!arc(c_tempo,l_tempo,c_tempo,l_tempo-1) && !arc(c_tempo,l_tempo,c_tempo,l_tempo+1)) {
            /* on avance donc d'une colonne */
            c_tempo++;
        }
        /* ici la pos (c_tempo,l_tempo) est propice à l'embuscade */
        return next_move(c,l,c_tempo,l_tempo);

    case LEFT:
        /* si le pacman se dirige vers la gauche on va chercher le prochain carrefour dans cette direction */
        while (!arc(c_tempo,l_tempo,c_tempo,l_tempo-1) && !arc(c_tempo,l_tempo,c_tempo,l_tempo+1)) {
            /* on recule donc d'une colonne */
            c_tempo--;
        }
        /* ici la pos (c_tempo,l_tempo) est propice à l'embuscade */
        return next_move(c,l,c_tempo,l_tempo);

    default:
        break;
    }

}

int Graph::next_random_move(int c, int l, int direction){

    /* les directons possibles */

    int directions[3] = {0,0,0};
    int nb_choix = 0;
    int random_direction;

    switch(direction){
        case UP:
        /* on regarde a gauche si il y a un chemin */
        if(arc(c,l,c-1,l) == 1){
            directions[nb_choix] = LEFT;
            nb_choix++;
        }
        /* on regarde a droite si il y a un chemin */
        if(arc(c,l,c+1,l) == 1){
            directions[nb_choix] = RIGHT;
            nb_choix++;
        }
        /* on regarde aussi si l'on peut continuer tout droit */
        if(arc(c,l,c,l-1) == 1){
            directions[nb_choix] = UP;
            nb_choix++;
        }
        if(nb_choix){
            random_direction = rand()%nb_choix;
            return directions[random_direction];
        }
        else return DOWN;

    case DOWN:
        /* on regarde a gauche si il y a un chemin */
        if(arc(c,l,c-1,l) == 1){
            directions[nb_choix] = LEFT;
            nb_choix++;
        }
        /* on regarde a droite si il y a un chemin */
        if(arc(c,l,c+1,l) == 1){
            directions[nb_choix] = RIGHT;
            nb_choix++;
        }
        /* on regarde aussi si l'on peut continuer tout droit */
        if(arc(c,l,c,l+1) == 1){
            directions[nb_choix] = DOWN;
            nb_choix++;
        }

        if(nb_choix){
            random_direction = rand()%nb_choix;
            return directions[random_direction];
        }
        else return UP;

    case LEFT:
        /* on regarde en bas si il y a un chemin */
        if(arc(c,l,c,l+1) == 1){
            directions[nb_choix] = DOWN;
            nb_choix++;
        }
        /* on regarde en haut si il y a un chemin */
        if(arc(c,l,c,l-1) == 1){
            directions[nb_choix] = UP;
            nb_choix++;
        }
        /* on regarde aussi si l'on peut continuer tout droit */
        if(arc(c,l,c-1,l) == 1){
            directions[nb_choix] = LEFT;
            nb_choix++;
        }
        if(nb_choix){
            random_direction = rand()%nb_choix;
            return directions[random_direction];
        }
        else return RIGHT;

    case RIGHT:
        /* on regarde en bas si il y a un chemin */
        if(arc(c,l,c,l+1) == 1){
            directions[nb_choix] = DOWN;
            nb_choix++;
        }
        /* on regarde en haut si il y a un chemin */
        if(arc(c,l,c,l-1) == 1){
            directions[nb_choix] = UP;
            nb_choix++;
        }
        /* on regarde aussi si l'on peut continuer tout droit */
        if(arc(c,l,c+1,l) == 1){
            directions[nb_choix] = RIGHT;
            nb_choix++;
        }
        if(nb_choix){
            random_direction = rand()%nb_choix;
            return directions[random_direction];
        }
        else return LEFT;

    }
}

void Graph::affiche_routage() const{
    for(int k=0;k<m_map_width*m_map_width;k++){
        for(int l=0;l<m_map_width*m_map_width;l++){
            cout << routage[l][k] << " ";
        }
        cout << endl;
    }
}

void Graph::calcule_routage(){

    int prec[m_map_width*m_map_height];
    int k,m;

    for(int target=0;target<m_map_width*m_map_height;target++){
        for(int j=0;j<m_map_width*m_map_height;j++){
            routage[target][j] = -1;
        }

    }

    /* pour toutes les sources possibles */
    for(int i=0;i<m_map_width;i++){
        for(int j=0;j<m_map_height;j++){
            Dijkstra(i,j,prec);
            /* pour toutes les cibles possibles */
            for(int target=0;target<m_map_width*m_map_height;target++){
                m = target;
                /* si cette cible a pu etre atteinte par dijkstra */
                if(prec[target] != -1){
                    /* tant que l'on est pas revenu à la source */
                    k=0;
                    while (prec[m] != m) {
                        k = m;
                        m = prec[m];
                    }
                    /* le prochain mouvement en partant de cette source pour aller à cette cible est k */
                    routage[i*m_map_width+j][target] = k;
                }

            }
        }
    }


}

int Graph::parse_move_c(int move){
    return move%m_map_width;
}

int Graph::parse_move_l(int move){
    int c = parse_move_c(move);
    return (move-c)/m_map_width;
}

int Graph::next_move(int c1, int l1, int c2, int l2){
    int x = l1*m_map_width+c1;
    int y = l2*m_map_width+c2;

    return routage[x][y];
}

int Graph::findMin(QList<int> *front, int dist[]) const{
    int min = INT_MAX;
    int min_i = 0;
    int i=0;
    int k=i;


    for(i=0;i<front->size();i++){

        if(dist[front->at(i)] < min){
            k = i;
            min_i = front->at(i);
            min = dist[front->at(i)];
        }
    }
    front->removeAt(k);

    return min_i;
}

void Graph::Dijkstra(int l1, int c1,int prec[]) const {
    int source = l1*m_map_width+c1;

    int dist[m_map_width*m_map_width];
    int dejavu[m_map_width*m_map_width];

    int min;
    QList<int> front;
    front.append(source);

    for(int i=0;i<m_map_width*m_map_width;i++){
        dist[i] = INT_MAX;
        dejavu[i] = 0;
        prec[i] = -1;
    }

    dejavu[source] = 1;
    dist[source] = 0;
    prec[source] = source;

    while (!front.isEmpty()) {

        min = findMin(&front,dist); /* ceci fait le remove du front */

        //cout << "sommet choisit " << min << endl;

        for(int i = 0;i<m_map_width*m_map_width;i++){
            if(a[min][i]){
                if(!dejavu[i]){
                    //cout << "okay on ajoute " << i << endl;
                    front.append(i);
                    dejavu[i] = 1;
                }
                if(dist[i] > (dist[min] + 1)){
                    dist[i] = dist[min] + 1;
                    prec[i] = min;
                }
            }
        }
    }
    prec;
}

void Graph::affiche() const{
    for(int k=0;k<m_map_width*m_map_width;k++){
        for(int l=0;l<m_map_width*m_map_width;l++){
            cout << a[l][k] << " ";
        }
        cout << endl;
    }
}

void Graph::initMatrice(){
    for(int k=0;k<m_map_width*m_map_width;k++){
        for(int l=0;l<m_map_width*m_map_width;l++){
            a[l][k] = 0;
        }
    }
}

void Graph::setArc(int l1, int c1, int l2, int c2){
    int x = l1*m_map_width + c1; /* use non static field instead 24 */
    int y = l2*m_map_width + c2;

    a[x][y] = 1;
}

int Graph::arc(int c1, int l1, int c2, int l2){

    int x = l1*m_map_width + c1; /* use non static field instead 24 */
    int y = l2*m_map_width + c2;

    return a[x][y];
}
