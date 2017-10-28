#include "controleur.h"

Controleur::Controleur(Modele* modele)
{
    partieEnCours = false;
    this->modele = modele;
    this->startTimer();
}
Modele* Controleur::getModele(){
    return modele;
}

int Controleur::getProchainMvmt(){
    return prochainMvmt;
}
void Controleur::setProchainMvmt(int mvmt){
    prochainMvmt = mvmt;
}


void Controleur::startTimer(){
    partieEnCours = true;
    std::thread AThread(&Controleur::threadCall, this);
    AThread.detach();
}

void Controleur::finPartie(int etat){   //etat == 0 -> Victoire, etat == 1 -> Défaite;
    if(etat == 0){
        std::cout << "VICTOIRE !" << std::endl;
    }
    else if (etat == 1){
        std::cout << "Defaite." << std::endl;
    }
    partieEnCours = false;
}

void Controleur::threadCall(){
    std::cout << "Partie commencee !" << std::endl;
    int acc = 0;

    /*int nbDeplacements = 0;
    Sommet* nextSommet = new Sommet();
    bool collision = false;*/
    while (partieEnCours) {
       std::this_thread::sleep_for(std::chrono::milliseconds(32)); //30 FPS ?

       //Calcul du temps.
       acc++;
       if(acc == 30){
            this->getModele()->setMin(this->getModele()->getMin()+1);
            std::cout << this->getModele()->getMin() << std::endl;
            acc = 0;

            /* Gestion du mode Berserk.
            if(this->getModele()->getTimerModeBerserk() > 1) this->getModele()->setTimerModeBerserk(this->getModele()->getTimerModeBerserk()-1);
            else {
                this->getModele()->setTimerModeBerserk(0);
                this->getModele()->setModeBerserk(false);
                this->getModele()->setKillStreak(0);
            }
              */
       }


       //Déplacement des éléments.

       /*
        collision = 0;
        for(Fantome f : this->getModele()->tabFantomes){


            //S'il y a intersection entre la hitbox du PacMan et celle d'un fantôme, il y a collision.
            if((this->getModele()->pcmn.hitbox).intersects(f.hitbox)){
                //Animation de collision ?
                collision = 1;
            }
         }
         if (collision == 0){

            //Si on a fait assez de déplacement pour arriver sur un nouveau sommet :
            if(nbDeplacements == D-1){        //D = nombre de déplacements entre les différents sommets. On met -1 puisqu'on déplace le PacMan à la fin (permet de connaitre l'environnement dans lequel va bouger le Pacman avant de le redessiner).
              nbDeplacements = 0;

              nextSommet = this->nextSommet(this->getModele()->pcmn);

              //On vérifie s'il y a des gommes dans ce nouveau sommet :
              if (nextSommet.getGum() == true){
                 this->getModele()->nbGommes--;
                 if(this->getModele()->nbGommes == 0){  //Fin de partie;
                    this->finPartie(0);
                 }
                 nextSommet.clearGum();
                 //nextSommet.redraw(); ?
              }
              else if (nextSommet.getBigGum() == true){
                 this->getModele()->setModeBerserk(timerADeterminePourLeBerserk);
                 nextSommet.clearGum();
                 //nextSommet.redraw(); ?
              }

              //Et on passe le pacMan au nouveau sommet :
              this->getModele()->pcmn->setSommet(nextSommet);
            }

            this->getModele()->pcmn.move();
            nbDeplacements++;

            //GERER LE NOUVEAU DEPLACEMENT.



            for(Fantome f : this->getModele()->tabFantomes){
              f.move();

              //Si nécessaire de conserver l'aspect "Sommet" pour les fantomes, ajouter ici une gestion du nombre de déplacements de la même manière que pour le Pacman.
            }
         }
         else {
            if(this->getModele()->getModeBerserk() == true){       //Si on a mangé une gomme qui permet de manger les fantômes et que son pouvoir est encore actif.
                this->getModele()->setKillStreak(this->getModele()->getKillStreak()+1); //Si KillStreak commence à 0, sinon mettre après.
                this->getModele()->ajouter_points(200*this->getModele()->getKillStreak());
            }
            else {
                if(this->getModele()->vie != 1){
                    this->getModele()->resetPlacementApresMort();
                }
                else {
                    //Faire une animation ?
                    this->finPartie(1);
                }
            }
         }

       */

    }
    std::cout << "Partie terminee !" << std::endl;
}


/*Sommet* Controleur::nextSommet(Entite e){

    if (e.dir[0] == 1 && e.dir[1] == 0)             //Droite
      return e->sommet->getSDroite();

    if (e.dir[0] == -1 && e.dir[1] == 0)            //Gauche
     return e->sommet->getSGauche();

    if (e.dir[0] == 0 && e.dir[1] == 1)             //Haut
      return e->sommet->getSHaut();

    if (e.dir[0] == 0 && e.dir[1] == -1)            //Bas
      return e->sommet->getSBas();

}
    */



