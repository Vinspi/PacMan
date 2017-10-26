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


void Controleur::startTimer(){
    partieEnCours = true;
    std::thread AThread(&Controleur::threadCall, this);
    AThread.detach();
}

void Controleur::finPartie(){
    partieEnCours = false;
}

void Controleur::threadCall(){
    std::cout << "Partie commencee !" << std::endl;
    int acc = 0;

    /*int posx = 0, posy = 0;
    int fposx = 0, fposy = 0, fmposx = 0, fmposy = 0;
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
        posx = this->getModele()->pcmn.x + (X)*this->getModele()->pcmn.dir[0]; //Position du PacMan après déplacement horizontal X (X valeur du déplacement dans la fonction move).
        posy = this->getModele()->pcmn.t + (Y)*this->getModele()->pcmn.dir[1]; //Position du PacMan après déplacement vertical Y (Y valeur du déplacement dans la fonction move).

        for(Fantome f : this->getModele()->tabFantomes){
            fposx = f.x + (X'+f.taille)*f.dir[0];   //Bout du fantome dans le sens de son déplacement (<=> avant du fantome).
            fposxop = f.x + X'+(f.taille)*f.dir[0];  //Bout du fantome dans le sens inverse de son déplacement (<=> arrière du fantome).
            fposy = f.y + (Y'+f.taille)*f.dir[1];
            fposyop = f.y + Y'+(f.taille)*f.dir[1];


            //Si le bout d'une entité après déplacement se trouve entre les deux bouts d'une entité opposée, c'est qu'il y a contact.
            if( (fposx <= posx+this->getModele()->pcmn.taille && fposx >= posx-this->getModele()->pcmn.taille) || (fposxop <= posx+this->getModele()->pcmn.taille && fposxop >= posx-this->getModele()->pcmn.taille) || (fposy <= posy+this->getModele()->pcmn.taille && fposy >= posy-this->getModele()->pcmn.taille) || (fposyop <= posy+this->getModele()->pcmn.taille && fposyop >= posy-this->getModele()->pcmn.taille)){
                //Animation de collision ?
                collision = 1;
            }
         }
         if (collision == 0){
            this->getModele()->pcmn.move();
            //Vérifier les gommes toussa.



            for(Fantome f : this->getModele()->tabFantomes){
              f.move();
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
                    this->finPartie();
                }
            }
         }

       */

    }
    std::cout << "Partie terminee !" << std::endl;
}





