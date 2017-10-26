#ifndef MODELE_H
#define MODELE_H

#include <iostream>       // std::cout


class Modele
{
public:
    Modele();
    int getMin();
    void setMin(int min);

private:
   //Niveau niveau; //Contiendra le graphe généré à partir du fichier_niveau.
    int min;

    //Valeurs normalement dans le Niveau :
    //PacMan pcmn;
    //std::vector<Fantome> tabFantomes;
    //nbGommes ?
    //int vie;


    //bool modeBerserk;
    //int timerModeBerserk;

};

#endif // MODELE_H
