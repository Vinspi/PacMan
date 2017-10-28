#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "modele.h"
#include "sommet.h"

class Controleur
{
public:
    Controleur(Modele* modele);
    void startTimer();
    void finPartie(int etat);
    void setModele(Modele modele);
    Modele* getModele();
    //Sommet* nextSommet(Entite e);

    void setProchainMvmt(int mvmt);
    int getProchainMvmt();

private:
        Modele* modele;
        void threadCall();

        bool partieEnCours;
        int prochainMvmt;

};

#endif // CONTROLEUR_H
