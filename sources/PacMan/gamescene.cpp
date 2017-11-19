#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>
#include <iostream>

using namespace std;

GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), m_timer(), m_timer_berzerk_mode()
{
    this->tm = tm;
    m_timer.setInterval(40);
    m_timer_berzerk_mode.setInterval(1000);

    connect(&m_timer,&QTimer::timeout,this,&GameScene::updateScene);
    connect(&m_timer_berzerk_mode,&QTimer::timeout,this,&GameScene::updateBerzerkMode);

    m_timer.start();
}

void GameScene::updateBerzerkMode(){

    if(m_time_elapsed_berzerk_mode == BERZERK_MODE_TIME){
        /* on retire le berzerk mode */


        Ghost *tmp;

        if(FlashAfraidGhost *fg = dynamic_cast<FlashAfraidGhost *> (blinky)){
            tmp = blinky;
            removeItem(blinky);

            blinky = new Blinky();
            blinky->setPos(tmp->pos());
            blinky->setSpawnPoint(tmp->spawnPoint());
            addItem(blinky);

            delete tmp;
        }
        if(FlashAfraidGhost *fg2 = dynamic_cast<FlashAfraidGhost *> (inky)){
            tmp = inky;
            removeItem(inky);

            inky = new Inky();
            inky->setPos(tmp->pos());
            inky->setSpawnPoint(tmp->spawnPoint());
            addItem(inky);

            delete tmp;
        }
        if(FlashAfraidGhost *fg3 = dynamic_cast<FlashAfraidGhost *> (pinky)){
            tmp = pinky;
            removeItem(pinky);

            pinky = new Pinky();
            pinky->setPos(tmp->pos());
            pinky->setSpawnPoint(tmp->spawnPoint());
            addItem(pinky);

            delete tmp;
        }
        if(FlashAfraidGhost *fg4 = dynamic_cast<FlashAfraidGhost *> (clyde)){
            tmp = clyde;
            removeItem(clyde);

            clyde = new Clyde();
            clyde->setPos(tmp->pos());
            clyde->setSpawnPoint(tmp->spawnPoint());
            addItem(clyde);

            delete tmp;
        }

        berzerk_mode_active = false;
        m_timer_berzerk_mode.stop();
    }
    else if(m_time_elapsed_berzerk_mode > (BERZERK_MODE_TIME/2)) {
        /* mon pikachu évolue en pikachu clignotant !!! */

        Ghost *tmp;

        if(AfraidGhost *fg = dynamic_cast<AfraidGhost *> (blinky)){
            tmp = blinky;
            removeItem(blinky);

            blinky = new FlashAfraidGhost();
            blinky->setPos(tmp->pos());
            blinky->setSpawnPoint(tmp->spawnPoint());
            addItem(blinky);

            delete tmp;
        }
        if(AfraidGhost *fg2 = dynamic_cast<AfraidGhost *> (inky)){
            tmp = inky;
            removeItem(inky);

            inky = new FlashAfraidGhost();
            inky->setPos(tmp->pos());
            inky->setSpawnPoint(tmp->spawnPoint());
            addItem(inky);

            delete tmp;
        }
        if(AfraidGhost *fg3 = dynamic_cast<AfraidGhost *> (pinky)){
            tmp = pinky;
            removeItem(pinky);

            pinky = new FlashAfraidGhost();
            pinky->setPos(tmp->pos());
            pinky->setSpawnPoint(tmp->spawnPoint());
            addItem(pinky);

            delete tmp;
        }
        if(AfraidGhost *fg4 = dynamic_cast<AfraidGhost *> (clyde)){
            tmp = clyde;
            removeItem(clyde);

            clyde = new FlashAfraidGhost();
            clyde->setPos(tmp->pos());
            clyde->setSpawnPoint(tmp->spawnPoint());
            addItem(clyde);

            delete tmp;
        }

        m_time_elapsed_berzerk_mode++;
    }
    else {
        m_time_elapsed_berzerk_mode++;
    }
}

void GameScene::updateScene()
{
    QPoint pos_pacman = Pacman->current_tile_pos();
    berzerk_debuff_vitesse = !berzerk_debuff_vitesse;

    hud->updateTime();

    /* pour clyde */

    for(int i=0;i<clyde->vitesse();i++){
        clyde->nextIAMove(graph_control,Pacman);
        clyde->avance();
        if(checkCollisionsGhost(clyde)){
            clyde->avance();
            checkCollisionsGhost(clyde);
        }
    }
    clyde->nextTile();
    /*********************************************************************/

    /* pour blinky */
    for(int i=0;i<blinky->vitesse();i++){
        blinky->nextIAMove(graph_control,Pacman);
        blinky->avance();
        if(checkCollisionsGhost(blinky)){
            blinky->avance();
            checkCollisionsGhost(blinky);
        }
    }
    blinky->nextTile();
    /*********************************************************************/

    /* pour inky */
    for(int i=0;i<inky->vitesse();i++){
        inky->nextIAMove(graph_control,Pacman);
        inky->avance();
        if(checkCollisionsGhost(inky)){
            inky->avance();
            checkCollisionsGhost(inky);
        }

    }
    inky->nextTile();
    /*********************************************************************/

    /* pour pinky */
    for(int i=0;i<pinky->vitesse();i++){
        pinky->nextIAMove(graph_control,Pacman);
        pinky->avance();
        if(checkCollisionsGhost(pinky)){
            pinky->avance();
            checkCollisionsGhost(pinky);
        }

    }
    pinky->nextTile();
    /*********************************************************************************************************************/

    /* pour pacman */
    for(int i=0;i<Pacman->vitesse();i++){
        Pacman->setDirection(next_move);
        Pacman->avance();

        if(checkCollisions()){
            Pacman->avance();
            checkCollisions();
        }
    }
    Pacman->nextTile();
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
    berzerk_debuff_vitesse = true;
    setSceneRect(0, 0, map.width() * T_SIZE, map.height() * T_SIZE);
    QPixmap bg(map.width() * T_SIZE, map.height() * T_SIZE);
    bg.fill(Qt::black);
    background = addPixmap(bg);
    labyrinthe = addPixmap(tm->drawTileMap(map));
    Pacman = new PacMan();
    blinky = new Blinky();
    clyde = new Clyde();
    inky = new Inky();
    pinky = new Pinky();
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


    SpawnBlocClyde *sbc = new SpawnBlocClyde();
    sbc->setPos(map.get_pos_clyde_init_col()*T_SIZE,map.get_pos_clyde_init_row()*T_SIZE);
    addItem(sbc);

    SpawnBlocInky *sbi = new SpawnBlocInky();
    sbi->setPos(map.get_pos_inky_init_col()*T_SIZE,map.get_pos_inky_init_row()*T_SIZE);
    addItem(sbi);

    SpawnBlocPinky *sbp = new SpawnBlocPinky();
    sbp->setPos(map.get_pos_pinky_init_col()*T_SIZE,map.get_pos_pinky_init_row()*T_SIZE);
    addItem(sbp);

    SpawnBlocBlinky *sbb = new SpawnBlocBlinky();
    sbb->setPos(map.get_pos_blinky_init_col()*T_SIZE,map.get_pos_blinky_init_row()*T_SIZE);
    addItem(sbb);

    Pacman->setPos(map.get_pos_pacman_init_col()*T_SIZE,map.get_pos_pacman_init_row()*T_SIZE);
    addItem(Pacman);

    blinky->setPos(map.get_pos_blinky_init_col()*T_SIZE,map.get_pos_blinky_init_row()*T_SIZE);
    blinky->setSpawnPoint(QPoint(map.get_pos_blinky_init_col(),map.get_pos_blinky_init_row()));
    clyde->setPos(map.get_pos_clyde_init_col()*T_SIZE,map.get_pos_clyde_init_row()*T_SIZE);
    clyde->setSpawnPoint(QPoint(map.get_pos_clyde_init_col(),map.get_pos_clyde_init_row()));
    inky->setPos(map.get_pos_inky_init_col()*T_SIZE,map.get_pos_inky_init_row()*T_SIZE);
    inky->setSpawnPoint(QPoint(map.get_pos_inky_init_col(),map.get_pos_inky_init_row()));
    pinky->setPos(map.get_pos_pinky_init_col()*T_SIZE,map.get_pos_pinky_init_row()*T_SIZE);
    pinky->setSpawnPoint(QPoint(map.get_pos_pinky_init_col(),map.get_pos_pinky_init_row()));



    addItem(blinky);
    addItem(clyde);
    addItem(inky);
    addItem(pinky);

    /* test */

    hud = new HUD(4);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();

    proxy->setWidget(hud);

    proxy->setPos(-200,0);

    addItem(proxy);


    /*********************/


}

int GameScene::checkCollisionsGhost(Ghost *ghost)
{

    int resultat = 0;
    Ghost *tmp;
    QList<QGraphicsItem *> list = collidingItems(ghost);

    for(int i = 0; i < list.size(); i++)
    {
        if(MurItem *b = dynamic_cast<MurItem *>(list.at(i))){
            ghost->annule_deplacement();
            resultat = 1;

        }
     }
     if(DeadGhost *dg = dynamic_cast<DeadGhost *>(ghost)){
         for(int i = 0; i < list.size(); i++){
                if(SpawnBlocBlinky *sbb = dynamic_cast<SpawnBlocBlinky *>(list.at(i))){
                    if(blinky == ghost){
                        tmp = blinky;
                        removeItem(blinky);

                        blinky = new Blinky();
                        blinky->setPos(tmp->pos());
                        blinky->setSpawnPoint(tmp->spawnPoint());
                        addItem(blinky);

                        delete tmp;
                    }
                }
                else if(SpawnBlocClyde *sbc = dynamic_cast<SpawnBlocClyde *>(list.at(i))){
                    if(clyde == ghost){
                        tmp = clyde;
                        removeItem(clyde);

                        clyde = new Clyde();
                        clyde->setPos(tmp->pos());
                        clyde->setSpawnPoint(tmp->spawnPoint());
                        addItem(clyde);

                        delete tmp;
                    }
                }
                else if(SpawnBlocPinky *sbp = dynamic_cast<SpawnBlocPinky *>(list.at(i))){
                    if(pinky == ghost){
                        tmp = pinky;
                        removeItem(pinky);

                        pinky = new Pinky();
                        pinky->setPos(tmp->pos());
                        pinky->setSpawnPoint(tmp->spawnPoint());
                        addItem(pinky);

                        delete tmp;
                    }
                }
                else if(SpawnBlocInky *sbi = dynamic_cast<SpawnBlocInky *>(list.at(i))){
                    if(inky == ghost){
                        tmp = inky;
                        removeItem(inky);

                        inky = new Inky();
                        inky->setPos(tmp->pos());
                        inky->setSpawnPoint(tmp->spawnPoint());
                        addItem(inky);

                        delete tmp;
                    }
                }
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
            hud->addToScore(d->value());
            m_nb_dot--;

        }
        else if(SuperDotItem *sd = dynamic_cast<SuperDotItem *>(list.at(i))){
            removeItem(list.at(i));
            delete list.at(i);
            hud->addToScore(sd->value());
            m_nb_dot--;
            Ghost *tmp;
            /* enable beast mode on pacman */
            /* mettre le mode pucelle sur tous les fantômes */
            DeadGhost *fg = dynamic_cast<DeadGhost *> (blinky);
            DeadGhost *fg2 = dynamic_cast<DeadGhost *> (inky);
            DeadGhost *fg3 = dynamic_cast<DeadGhost *> (pinky);
            DeadGhost *fg4 = dynamic_cast<DeadGhost *> (clyde);
            if(!fg){
                tmp = blinky;
                removeItem(blinky);

                blinky = new AfraidGhost();
                blinky->setPos(tmp->pos());
                blinky->setSpawnPoint(tmp->spawnPoint());
                addItem(blinky);

                delete tmp;
            }
            if(!fg2){
                tmp = inky;
                removeItem(inky);

                inky = new AfraidGhost();
                inky->setPos(tmp->pos());
                inky->setSpawnPoint(tmp->spawnPoint());
                addItem(inky);

                delete tmp;
            }
            if(!fg3){
                tmp = pinky;
                removeItem(pinky);

                pinky = new AfraidGhost();
                pinky->setPos(tmp->pos());
                pinky->setSpawnPoint(tmp->spawnPoint());
                addItem(pinky);

                delete tmp;
            }
            if(!fg4){
                tmp = clyde;
                removeItem(clyde);

                clyde = new AfraidGhost();
                clyde->setPos(tmp->pos());
                clyde->setSpawnPoint(tmp->spawnPoint());
                addItem(clyde);

                delete tmp;
            }
            berzerk_mode_active = true;
            m_time_elapsed_berzerk_mode = 0;
            m_timer_berzerk_mode.start();


        }
        else if(MurItem *b = dynamic_cast<MurItem *>(list.at(i))){
            Pacman->annule_deplacement();
            resultat = 1;

        }
        else if(AfraidGhost *ag = dynamic_cast<AfraidGhost *>(list.at(i))){
            /* detruire le fantôme */
            QPointF pos_ghost = ag->pos();

            removeItem(ag);

            Ghost *tmp;

            if(ag == clyde){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(clyde->spawnPoint());
                tmp->setPos(clyde->pos());
                delete clyde;
                clyde = tmp;
                addItem(clyde);
            }
            else if(ag == inky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(inky->spawnPoint());
                tmp->setPos(inky->pos());
                delete inky;
                inky = tmp;
                addItem(inky);
            }
            else if(ag == pinky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(pinky->spawnPoint());
                tmp->setPos(pinky->pos());
                delete pinky;
                pinky = tmp;
                addItem(pinky);
            }
            else if(ag == blinky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(blinky->spawnPoint());
                tmp->setPos(blinky->pos());
                delete blinky;
                blinky = tmp;
                addItem(blinky);
            }

        }
        else if(FlashAfraidGhost *ag = dynamic_cast<FlashAfraidGhost *>(list.at(i))){
            /* detruire le fantôme */
            QPointF pos_ghost = ag->pos();

            removeItem(ag);

            Ghost *tmp;

            if(ag == clyde){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(clyde->spawnPoint());
                tmp->setPos(clyde->pos());
                delete clyde;
                clyde = tmp;
                addItem(clyde);
            }
            else if(ag == inky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(inky->spawnPoint());
                tmp->setPos(inky->pos());
                delete inky;
                inky = tmp;
                addItem(inky);
            }
            else if(ag == pinky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(pinky->spawnPoint());
                tmp->setPos(pinky->pos());
                delete pinky;
                pinky = tmp;
                addItem(pinky);
            }
            else if(ag == blinky){
                tmp = new DeadGhost();
                tmp->setSpawnPoint(blinky->spawnPoint());
                tmp->setPos(blinky->pos());
                delete blinky;
                blinky = tmp;
                addItem(blinky);
            }


        }
        else if(DeadGhost *dg = dynamic_cast<DeadGhost *>(list.at(i))){
            /* ne rien faire */
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
