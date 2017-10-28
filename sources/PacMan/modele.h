#ifndef MODELE_H
#define MODELE_H

#include <iostream>       // std::cout


class Modele
{
public:
    Modele();
    int getMin();
    void setMin(int min);

    int getVie();
    void setVie(int vie);


    int getTimerBerserk();
    void setTimerBerserk(int timer);

    bool getModeBerserk();
    void setModeBerserk(bool mode);

    void resetPlacementApresMort();

private:
   //Niveau niveau; //Contiendra le graphe généré à partir du fichier_niveau.

    //Valeurs normalement dans le Niveau ? :
    //PacMan pcmn;
    //nbGommes ?
    //std::vector<Fantome> tabFantomes;

    //A mettre dans les entites ?
    //std::vector<int> positionsInitialesFantomes;
    //int positionInitalePacMan;


    int min;
    int vie;
    bool modeBerserk;
    int timerModeBerserk;

};

#endif // MODELE_H
