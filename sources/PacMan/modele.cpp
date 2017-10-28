#include "modele.h"


Modele::Modele()
{
    this->min = 0;
}

void Modele::setMin(int min){
    this->min = min;
}
int Modele::getMin(){
    return min;
}

void Modele::setVie(int vie){
    this->vie = vie;
}
int Modele::getVie(){
    return vie;
}

void Modele::setTimerBerserk(int timer){
    this->timerModeBerserk = timer;
}
int Modele::getTimerBerserk(){
    return timerModeBerserk;
}

void Modele::setModeBerserk(bool mode){
    this->modeBerserk = mode;
}
bool Modele::getModeBerserk(){
    return modeBerserk;
}


void Modele::resetPlacementApresMort(){
    this->setVie(this->getVie()-1);
    /*this->pcmn.pos = this->pcmn.posInit;
    for(Fantome f : tabFantomes){
        f.pos = f.posInit;
    }*/
}
