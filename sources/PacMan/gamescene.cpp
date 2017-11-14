#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>
#include <iostream>

using namespace std;

GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), m_timer(), m_timer_berzerk_mode()
{
    this->tm = tm;
    m_timer.setInterval(10);
    m_timer_berzerk_mode.setInterval(1000);

    connect(&m_timer,&QTimer::timeout,this,&GameScene::updateScene);
    connect(&m_timer_berzerk_mode,&QTimer::timeout,this,&GameScene::updateBerzerkMode);

    m_timer.start();
}

void GameScene::updateBerzerkMode(){
    if(m_time_elapsed_berzerk_mode == BERZERK_MODE_TIME){
        /* on retire le berzerk mode */
        QPointF pos_blinky = blinky->pos();
        QPointF pos_clyde = clyde->pos();

        removeItem(blinky);
        removeItem(clyde);

        delete blinky;
        delete clyde;

        blinky = new Blinky();
        clyde = new Clyde();

        blinky->setPos(pos_blinky);
        clyde->setPos(pos_clyde);

        addItem(blinky);
        addItem(clyde);

        berzerk_mode_active = false;

        m_timer_berzerk_mode.stop();
    }
    else if(m_time_elapsed_berzerk_mode > (BERZERK_MODE_TIME/2)) {
        /* mon pikachu évolue en fantôme clignotant !!! */
        QPointF pos_blinky = blinky->pos();
        QPointF pos_clyde = clyde->pos();

        removeItem(blinky);
        removeItem(clyde);

        delete blinky;
        delete clyde;

        blinky = new FlashAfraidGhost();
        clyde = new FlashAfraidGhost();

        blinky->setPos(pos_blinky);
        clyde->setPos(pos_clyde);

        addItem(blinky);
        addItem(clyde);

        m_time_elapsed_berzerk_mode++;
    }
    else {
        m_time_elapsed_berzerk_mode++;
    }
}

void GameScene::updateScene(){

    if(berzerk_mode_active){
        QPoint pos_clyde = clyde->current_tile_pos();
        next_move_clyde = graph_control->next_random_move(pos_clyde.x(),pos_clyde.y(),clyde->direction());

        QPoint pos_blinky = blinky->current_tile_pos();
        next_move_blinky = graph_control->next_random_move(pos_blinky.x(),pos_blinky.y(),clyde->direction());

//        QPoint pos_inky = inky->current_tile_pos();
//        next_move_inky = graph_control->next_random_move(pos_inky.x(),pos_inky.y(),clyde->direction());

//        QPoint pos_pinky = pinky->current_tile_pos();
//        next_move_pinky = graph_control->next_random_move(pos_pinky.x(),pos_pinky.y(),clyde->direction());

        clyde->setDirection(next_move_clyde);
        clyde->avance();
        if(checkCollisionsGhost(clyde)){
            clyde->avance();
            checkCollisionsGhost(clyde);
        }

        blinky->setDirection(next_move_blinky);
        blinky->avance();
        if(checkCollisionsGhost(blinky)){
            blinky->avance();
            checkCollisionsGhost(blinky);
        }


//        inky->setDirection(next_move_inky);
//        inky->avance();
//        if(checkCollisionsGhost(inky)){
//            inky->avance();
//            checkCollisionsGhost(inky);
//        }


//        pinky->setDirection(next_move_pinky);
//        pinky->avance();
//        if(checkCollisionsGhost(pinky)){
//            pinky->avance();
//            checkCollisionsGhost(pinky);
//        }
    }
    else {
        /* pour clyde */

        QPoint pos_clyde = clyde->current_tile_pos();
        next_move_clyde = graph_control->next_random_move(pos_clyde.x(),pos_clyde.y(),clyde->direction());



        clyde->setDirection(next_move_clyde);
        clyde->avance();
        if(checkCollisionsGhost(clyde)){
            clyde->avance();
            checkCollisionsGhost(clyde);
        }

        /*********************************************************************/
        /* pour blinky */
        QPoint pos_blinky = blinky->current_tile_pos();
        QPoint pos_pacman = Pacman->current_tile_pos();

        int next_ghost_move = graph_control->next_move(pos_blinky.x(),pos_blinky.y(),pos_pacman.x(),pos_pacman.y());

        int next_move_c = graph_control->parse_move_c(next_ghost_move);
        int next_move_l = graph_control->parse_move_l(next_ghost_move);

        /* la direction sera LEFT */
        if(pos_blinky.x() > next_move_c){
            next_move_blinky = LEFT;

        }
        /* la direction sera RIGHT */
        if(pos_blinky.x() < next_move_c){
            next_move_blinky = RIGHT;

        }
        /* la direction sera UP */
        if(pos_blinky.y() > next_move_l){
            next_move_blinky = UP;

        }
        /* la direction sera DOWN */
        if(pos_blinky.y() < next_move_l){
            next_move_blinky = DOWN;

        }



        blinky->setDirection(next_move_blinky);
        blinky->avance();
        if(checkCollisionsGhost(blinky)){
            blinky->avance();
            checkCollisionsGhost(blinky);
        }
        /*********************************************************************************************************************/

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
    clyde = new Clyde();
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

    blinky->setPos(map.get_pos_blinky_init_col()*T_SIZE,map.get_pos_blinky_init_row()*T_SIZE);
    clyde->setPos(map.get_pos_clyde_init_col()*T_SIZE,map.get_pos_clyde_init_row()*T_SIZE);
    addItem(blinky);
    addItem(Pacman);
    addItem(clyde);



    //Pacman = addPixmap(QPixmap("../pacmanmoves").copy(0,28,14,14));
    //Pacman->setOffset(21, 198);
}

int GameScene::checkCollisionsGhost(Ghost *ghost)
{

    int resultat = 0;
    QList<QGraphicsItem *> list = collidingItems(ghost);

    for(int i = 0; i < list.size(); i++)
    {
        if(BlocItem *b = dynamic_cast<BlocItem *>(list.at(i))){
            ghost->annule_deplacement();
            resultat = 1;

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
        if(DotItem *d = dynamic_cast<DotItem *>(list.at(i)))
        {
            removeItem(list.at(i));
            delete list.at(i);
            score += d->value();
            m_nb_dot--;

        }
        else if(SuperDotItem *sd = dynamic_cast<SuperDotItem *>(list.at(i))){
            removeItem(list.at(i));
            delete list.at(i);
            score += sd->value();
            m_nb_dot--;
            /* enable beast mode on pacman */
            /* mettre le mode pucelle sur tous les fantômes */
            QPointF pos_blinky = blinky->pos();
            QPointF pos_clyde = clyde->pos();

            removeItem(blinky);
            removeItem(clyde);

            delete blinky;
            delete clyde;

            blinky = new AfraidGhost();
            clyde = new AfraidGhost();

            blinky->setPos(pos_blinky);
            clyde->setPos(pos_clyde);

            addItem(blinky);
            addItem(clyde);
            berzerk_mode_active = true;
            m_time_elapsed_berzerk_mode = 0;
            m_timer_berzerk_mode.start();


        }
        else if(BlocItem *b = dynamic_cast<BlocItem *>(list.at(i))){
            Pacman->annule_deplacement();
            resultat = 1;

        }
        else if(AfraidGhost *ag = dynamic_cast<AfraidGhost *>(list.at(i))){
            /* detruire le fantôme */
        }
        else if(FlashAfraidGhost *ag = dynamic_cast<FlashAfraidGhost *>(list.at(i))){
            /* detruire le fantôme */


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
