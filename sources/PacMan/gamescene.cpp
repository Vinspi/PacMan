#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>
#include <iostream>

using namespace std;

GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), m_timer()
{
    this->tm = tm;
    m_timer.setInterval(10);

    connect(&m_timer,&QTimer::timeout,this,&GameScene::updateScene);
    m_timer.start();
}

void GameScene::updateScene(){

    /* pour blinky */
    QPoint pos_blinky = blinky->current_tile_pos();
    QPoint pos_pacman = Pacman->current_tile_pos();

    int next_ghost_move = graph_control->next_move(pos_blinky.x(),pos_blinky.y(),pos_pacman.x(),pos_pacman.y());
//    cout << "blinky : ";
//    cout << pos_blinky.x() << " " << pos_blinky.y() << endl;
//    cout << "pacman : ";
//    cout << pos_pacman.x() << " " << pos_pacman.y() << endl;
//    cout << next_ghost_move << endl;

    int next_move_c = graph_control->parse_move_c(next_ghost_move);
    int next_move_l = graph_control->parse_move_l(next_ghost_move);

//    cout << "prochain saut " << next_move_c << " " << next_move_l << endl;

    /* la direction sera LEFT */
    if(pos_blinky.x() > next_move_c){
        next_move_blinky = LEFT;
        //blinky->setDirection(LEFT);
    }
    /* la direction sera RIGHT */
    if(pos_blinky.x() < next_move_c){
        next_move_blinky = RIGHT;
        //blinky->setDirection(RIGHT);
    }
    /* la direction sera UP */
    if(pos_blinky.y() > next_move_l){
        next_move_blinky = UP;
        //blinky->setDirection(UP);
    }
    /* la direction sera DOWN */
    if(pos_blinky.y() < next_move_l){
        next_move_blinky = DOWN;
        //blinky->setDirection(DOWN);
    }
    //blinky->setDirection(LEFT);


    blinky->setDirection(next_move_blinky);
    blinky->avance();
    if(checkCollisionsBlinky()){
        blinky->avance();
        checkCollisionsBlinky();
    }

    /* pour pacman */
    Pacman->setDirection(next_move);
    Pacman->avance();

    if(checkCollisions()){
        Pacman->avance();
        checkCollisions();
    }

    if(m_nb_dot == 0){
        win();
    }
    this->update();
}

void GameScene::init(TileMap &map)
{

    clear();
    m_nb_dot = 0;
    graph_control = new Graph(map);
    score = 0;
    next_move = UP;
    setSceneRect(0, 0, map.width() * T_SIZE, map.height() * T_SIZE);
    QPixmap bg(map.width() * T_SIZE, map.height() * T_SIZE);
    bg.fill(Qt::black);
    background = addPixmap(bg);
    labyrinthe = addPixmap(tm->drawTileMap(map));
    Pacman = new PacMan();
    blinky = new Blinky();

    //labyrinthe->setOffset(16, 16);

    CollectableItem *dot;
    BlocItem *mur;

    for(int i=0;i<map.width();i++){
        for(int j=0;j<map.height();j++){
            /* si c'est un bloc */
            if(map.tile(i,j) == 0){
                mur = new MurItem();
                mur->setPos(j*32,i*32);
                addItem(mur);
            }
        }
    }

    for(int i=0;i<map.width();i++){
        for(int j=0;j<map.height();j++){
            if(map.tile_collectibles(i,j) == 1){
                dot = new DotItem();
                dot->setPos(j*32,i*32);
                dots.append(dot);
                addItem(dot);
                m_nb_dot++;
            }
            if(map.tile_collectibles(i,j) == 2){
                dot = new SuperDotItem();
                dot->setPos(j*32,i*32);
                dots.append(dot);
                addItem(dot);
                m_nb_dot++;
            }
        }
    }

    //qDebug() << map.get_pos_pacman_init_col();
    Pacman->setPos(map.get_pos_pacman_init_col()*T_SIZE,map.get_pos_pacman_init_row()*T_SIZE);

    blinky->setPos(15*32,22*32);
    addItem(blinky);
    addItem(Pacman);



    //Pacman = addPixmap(QPixmap("../pacmanmoves").copy(0,28,14,14));
    //Pacman->setOffset(21, 198);
}

int GameScene::checkCollisionsBlinky()
{

    int resultat = 0;
    QList<QGraphicsItem *> list = collidingItems(blinky);

    for(int i = 0; i < list.size(); i++)
    {
        if(BlocItem *b = dynamic_cast<BlocItem *>(list.at(i))){
            blinky->annule_deplacement();
            resultat = 1;
           // qDebug() << "deplacement annulé" << endl;
        }
    }
    return resultat;
}

int GameScene::checkCollisions()
{

    int resultat = 0;
    QList<QGraphicsItem *> list = collidingItems(Pacman);

    for(int i = 0; i < list.size(); i++)
    {
        if(CollectableItem *d = dynamic_cast<CollectableItem *>(list.at(i)))
        {
            removeItem(list.at(i));
            delete list.at(i);
            score += d->value();
            m_nb_dot--;
            //qDebug() << "score" << score << endl;
        }
        else if(BlocItem *b = dynamic_cast<BlocItem *>(list.at(i))){
            Pacman->annule_deplacement();
            resultat = 1;
           // qDebug() << "deplacement annulé" << endl;
        }
        else if(Entity *e = dynamic_cast<Entity *>(list.at(i))){
            gameOver();
        }
    }
    return resultat;
}

void GameScene::gameOver(){
    m_timer.stop();
    qDebug() << "Game Over !";
}

void GameScene::win(){
    m_timer.stop();
    qDebug() << "winner !";
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch(event->key())
    {
        case Qt::Key_Right:
            next_move = RIGHT;
            //Pacman->setDirection(RIGHT);
            break;
        case Qt::Key_Left:
            next_move = LEFT;
            //Pacman->setDirection(LEFT);
            break;
        case Qt::Key_Down:
            next_move = DOWN;
            //Pacman->setDirection(DOWN);
            break;
        case Qt::Key_Up:
            next_move = UP;
            //Pacman->setDirection(UP);
            break;
        default:
            break;
    }

    checkCollisions();
}
