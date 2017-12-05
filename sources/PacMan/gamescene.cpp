#include "gamescene.h"
#include <QKeyEvent>
#include <QPixmap>
#include <iostream>
#include <QPushButton>
#include <QStackedWidget>

using namespace std;

GameScene::GameScene(TileManager *tm) : QGraphicsScene(), dots(), m_timer(), m_timer_berzerk_mode(), tilemap(), timerSpawnMysteryBloc()
{
    this->tm = tm;
    m_timer.setInterval(40);
    m_timer_berzerk_mode.setInterval(1000);

    connect(&m_timer,&QTimer::timeout,this,&GameScene::updateScene);
    connect(&m_timer_berzerk_mode,&QTimer::timeout,this,&GameScene::updateBerzerkMode);

    connect(&timerSpawnMysteryBloc,&QTimer::timeout,this,&GameScene::spawnMysteryBloc);


    srand(time(NULL));

    timerSpawnMysteryBloc.setInterval(5000);
    mystery_box_spawn = false;

}


void GameScene::updateTimerDebut(){

    if(compteur_timer_deb > 20){
        m_nombre_timer_deb->setStyleSheet(QString("color: rgba(0,0,0,%1);"
                                          "font-size: 200px;"
                                          "background: transparent;").arg(qreal(compteur_timer_deb-20)/10));
    }
    else if(compteur_timer_deb <= 20 && compteur_timer_deb > 10){
        if (compteur_timer_deb == 20){
            m_nombre_timer_deb->setText("2");
            m_nombre_timer_deb->setStyleSheet(QString("color: rgba(0,0,0,1);"
                                                      "font-size: 200px;"
                                                      "background: transparent;"));
        }
        else{
            m_nombre_timer_deb->setStyleSheet(QString("color: rgba(0,0,0,%1);"
                                              "font-size: 200px;"
                                              "background: transparent;").arg(qreal(compteur_timer_deb-10)/10));
        }
    }
    else {
        if(compteur_timer_deb == 10){
            m_nombre_timer_deb->setText("1");
            m_nombre_timer_deb->setStyleSheet(QString("color: rgba(0,0,0,1);"
                                                      "font-size: 200px;"
                                                      "background: transparent;"));
        }
        else if(compteur_timer_deb == 0){
            m_timer.start();
            timerSpawnMysteryBloc.start();

            m_nombre_timer_deb->setVisible(false);
            timer_debut->stop();

        }
        else{
            m_nombre_timer_deb->setStyleSheet(QString("color: rgba(0,0,0,%1);"
                                              "font-size: 200px;"
                                              "background: transparent;").arg(qreal(compteur_timer_deb)/10));
        }

    }
    compteur_timer_deb--;
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

    if(!(hud->updateTime())){
        gameOver(); /* gamover (timeout) */
    }

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

void GameScene::reset(){

    m_timer.stop();
    timerSpawnMysteryBloc.stop();
    Ghost *tmp_blinky = blinky;
    Ghost *tmp_clyde = clyde;
    Ghost *tmp_inky = inky;
    Ghost *tmp_pinky = pinky;
    PacMan *tmp_pacman = Pacman;

    Pacman = new PacMan();

    Pacman->setPos(pacman_spawn_point);
    Pacman->setLastPos(pacman_spawn_point);

    removeItem(tmp_pacman);
    addItem(Pacman);

    blinky = new Blinky();
    clyde = new Clyde();
    inky = new Inky();
    pinky = new Pinky();

    blinky->setPos(tmp_blinky->spawnPoint()*T_SIZE);
    blinky->setSpawnPoint(tmp_blinky->spawnPoint());

    clyde->setPos(tmp_clyde->spawnPoint()*T_SIZE);
    clyde->setSpawnPoint(tmp_clyde->spawnPoint());

    inky->setPos(tmp_inky->spawnPoint()*T_SIZE);
    inky->setSpawnPoint(tmp_inky->spawnPoint());

    pinky->setPos(tmp_pinky->spawnPoint()*T_SIZE);
    pinky->setSpawnPoint(tmp_pinky->spawnPoint());

    addItem(blinky);
    addItem(clyde);
    addItem(inky);
    addItem(pinky);

    removeItem(tmp_blinky);
    removeItem(tmp_pinky);
    removeItem(tmp_inky);
    removeItem(tmp_clyde);

    delete tmp_blinky;
    delete tmp_clyde;
    delete tmp_inky;
    delete tmp_pinky;

    compteur_timer_deb = 30;
    m_nombre_timer_deb->setText("3");
    m_nombre_timer_deb->setVisible(true);
    timer_debut->start();


}

void GameScene::init(TileMap &map)
{
    clear();
    m_nb_dot = 0;
    graph_control = new Graph(map);
    tilemap = map;
    score = 0;
    next_move = UP;
    berzerk_debuff_vitesse = true;
    setSceneRect(0, 0, map.width() * T_SIZE, map.height() * T_SIZE);

    /* background */

    QLabel *m_background = new QLabel();
    m_background->setGeometry(0,0,1280,800);
    m_background->setPixmap(QPixmap("../PacMan/graphics_pacman/background_pacman.png").scaled(1280,800));
    QGraphicsProxyWidget *proxy_tmp = new QGraphicsProxyWidget();

    proxy_tmp->setWidget(m_background);
    proxy_tmp->setPos(-255,-15);
    addItem(proxy_tmp);

    /******************/

    QPixmap bg(map.width() * T_SIZE, map.height() * T_SIZE);
    bg.fill(Qt::black);
    background = addPixmap(bg);
    labyrinthe = addPixmap(tm->drawTileMap(map));
    Pacman = new PacMan();
    blinky = new Blinky();
    clyde = new Clyde();
    inky = new Inky();
    pinky = new Pinky();


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

    pacman_spawn_point = QPoint(map.get_pos_pacman_init_col()*T_SIZE,map.get_pos_pacman_init_row()*T_SIZE);

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

    /* HUD */

    hud = new HUD(NB_VIE_LEVEL);
    proxy_hud = new QGraphicsProxyWidget();

    proxy_hud->setWidget(hud);

    proxy_hud->setPos(-200,0);

    addItem(proxy_hud);


    /*********************/


    /* pour le compteur de début de partie */


    m_nombre_timer_deb = new QLabel("3");
    m_nombre_timer_deb->setStyleSheet("color: rgba(0,0,0,1);"
                                      "font-size: 200px;"
                                      "background: transparent;"
                                      "opacity: 0.5;");




    timer_debut = new QTimer();

    connect(timer_debut,&QTimer::timeout,this,&GameScene::updateTimerDebut);

    timer_debut->setInterval(100); /* 10 clocks pour 1 sec */
    compteur_timer_deb = 30; /* 3 sec soit 30 clocks */
    timer_debut->start();



    tmp_prox = new QGraphicsProxyWidget();

    tmp_prox->setWidget(m_nombre_timer_deb);

    tmp_prox->setPos(width()/2-50,height()/2-120);

    addItem(tmp_prox);

    /****************************************/


    /***** nécéssaire au gameOver et au Win ***********/

    QLabel *gagne = new QLabel("GAGNE !");
    gagne->setStyleSheet("color: #ffffff;"
                       "font-size: 85px;"
                       "background: #2d2703;"
                       "padding: 10px 20px 10px 20px;"
                       "border: 5px solid #ffdb0f ;"
                       "text-decoration: none;");
    pwwin = new QGraphicsProxyWidget();
    pwwin->setWidget(gagne);
    pwwin->setPos(width()/2-200,height()/2-100);

    QPushButton *continuer = new QPushButton("continuer");
    continuer->setStyleSheet("color: #ffffff;"
                             "font-size: 50px;"
                             "background: #2d2703;"
                             "padding: 10px 20px 10px 20px;"
                             "border: 5px solid #ffdb0f ;"
                             "text-decoration: none;");

    pwcontinuer = new QGraphicsProxyWidget();
    pwcontinuer->setWidget(continuer);
    pwcontinuer->setPos(width()/2,height()/2+100);


    QLabel *gameOver = new QLabel("GAME OVER !");

    gameOver->setStyleSheet("color: #ffffff;"
                            "font-size: 85px;"
                            "background: #2d2703;"
                            "padding: 10px 20px 10px 20px;"
                            "border: 5px solid #ffdb0f ;"
                            "text-decoration: none;");

    pwgameover = new QGraphicsProxyWidget();
    pwgameover->setWidget(gameOver);
    pwgameover->setPos(width()/2-300,height()/2-100);



    QPushButton *retour = new QPushButton("retour");
    QPushButton *recommencer = new QPushButton("recommencer");

    pwretour = new QGraphicsProxyWidget();
    pwretour->setWidget(retour);

    pwrecommencer = new QGraphicsProxyWidget();
    pwrecommencer->setWidget(recommencer);

    pwretour->setPos(width()/2-300,height()/2+100);
    pwrecommencer->setPos(width()/2-50,height()/2+100);

    retour->setStyleSheet("color: #ffffff;"
                            "font-size: 50px;"
                            "background: #2d2703;"
                            "padding: 10px 20px 10px 20px;"
                            "border: 5px solid #ffdb0f ;"
                            "text-decoration: none;");

    recommencer->setStyleSheet("color: #ffffff;"
                            "font-size: 50px;"
                            "background: #2d2703;"
                            "padding: 10px 20px 10px 20px;"
                            "border: 5px solid #ffdb0f ;"
                            "text-decoration: none;");

    /* on connecte les boutons au bon slots */
    connect(retour,&QPushButton::clicked,this,&GameScene::on_click_retour);
    connect(recommencer,&QPushButton::clicked,this,&GameScene::on_click_recommencer);
    connect(continuer,&QPushButton::clicked,this,&GameScene::on_click_continuer);

    /*****************************************/



}

void GameScene::setActiveProfil(Profil *profil){
       activeProfile = profil;
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


void GameScene::enableBerzerkMode(){
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
        else if(MysteryBloc *mb = dynamic_cast<MysteryBloc *>(list.at(i))){
            /* en construction */
            MysteryItem *mi = mb->randomItem();
            hud->setMysteryItem(mi);
            m_mysteryItem = mi;
            timerSpawnMysteryBloc.start();
            removeItem(mb);
            delete mb;
            mystery_box_spawn = false;
            /********************/
        }
        else if(SuperDotItem *sd = dynamic_cast<SuperDotItem *>(list.at(i))){
            removeItem(list.at(i));
            delete list.at(i);
            hud->addToScore(sd->value());
            m_nb_dot--;
            enableBerzerkMode();


        }
        else if(MurItem *b = dynamic_cast<MurItem *>(list.at(i))){
            Pacman->annule_deplacement();
            resultat = 1;

        }
        else if(AfraidGhost *ag = dynamic_cast<AfraidGhost *>(list.at(i))){
            /* detruire le fantôme */
            QPointF pos_ghost = ag->pos();

            hud->addToScore(100);

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


            hud->addToScore(200);

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
            if(hud->nb_vie() > 0){
                hud->perd_une_vie();
                reset();
            }
            else {
                gameOver();
                break;
            }
        }
    }
    return resultat;
}

void GameScene::win(){
    //std::cout << "Profil " << activeProfile->getNom() << " niv max = " << activeProfile->getNivMax();
    QString level_actuel("");
    QStringList liste = tilemap.getFileName().split("");

    for(int i=27;i<liste.length();i++){

        if(!liste.at(i).compare(QString(".")))
               break;
        level_actuel = level_actuel+liste.at(i);
    }

    if(level_actuel.toInt() > activeProfile->getNivMax()){
        activeProfile->setNivMax(level_actuel.toInt());
        std::cout << "Nouveau niveau atteint pour " << activeProfile->getNom() << " : " << level_actuel.toInt();
        activeProfile->saveProfile("./profil/");
    }

    m_timer.stop();
    addItem(pwretour);
    if(level_actuel.toInt() < NB_NIV_MAX)
        addItem(pwcontinuer);

    addItem(pwwin);
}


void GameScene::gameOver(){
    m_timer.stop();
    qDebug() << "gameOver";


    addItem(pwretour);
    addItem(pwrecommencer);
    addItem(pwgameover);
}

void GameScene::on_click_continuer(){
    QString level_actuel("");
    QStringList liste = tilemap.getFileName().split("");

    for(int i=27;i<liste.length();i++){

        if(!liste.at(i).compare(QString(".")))
               break;
        level_actuel = level_actuel+liste.at(i);
    }

    QString niveau_suivant("../PacMan/levels/xml_level");
    niveau_suivant = niveau_suivant + QString::number(level_actuel.toInt()+1) + QString(".xml");
    removeItem(pwwin);
    removeItem(pwretour);
    removeItem(pwcontinuer);


    /* peut etre detruire quelques objets ici :/ */
    delete clyde;
    delete Pacman;
    delete blinky;
    delete inky;
    delete pinky;
    mystery_box_spawn = false;
    //qDebug() << niveau_suivant;
    TileMap *t = new TileMap(niveau_suivant);

    init(*t);

}

void GameScene::on_click_retour(){

    m_timer.stop();
    gv->setWid();
}

void GameScene::setGameView(GameView *g){
    gv = g;
}

void GameScene::on_click_recommencer(){

    removeItem(pwgameover);
    removeItem(pwrecommencer);
    removeItem(pwretour);

    /* peut etre detruire quelques objets ici :/ */
    delete clyde;
    delete Pacman;
    delete blinky;
    delete inky;
    delete pinky;
    mystery_box_spawn = false;
    init(tilemap);
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
        case Qt::Key_Space:
            useMysteryItem();
            break;
        default:
            break;
    }

    checkCollisions();
}


void GameScene::useMysteryItem(){
    if(m_mysteryItem){
        if(SuperDotItem *sdi = dynamic_cast<SuperDotItem *>(m_mysteryItem)){
            enableBerzerkMode();

        }
        hud->resetMysteryItem();
        delete m_mysteryItem;
        m_mysteryItem = nullptr;
    }
}

void GameScene::spawnMysteryBloc(){
    if(!mystery_box_spawn){
        int c;
        int l;
        mystery_box_spawn = true;
        do{
            c = rand()%24;
            l = rand()%24;
        }while(tilemap.tile(c,l) != 1);

        MysteryBloc *mb = new MysteryBloc();
        mb->setPos(c*T_SIZE,l*T_SIZE);
        addItem(mb);
    }

    timerSpawnMysteryBloc.stop();

}
