#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "modele.h"

class Controleur
{
public:
    Controleur(Modele* modele);
    void startTimer();
    void finPartie();
    void setModele(Modele modele);
    Modele* getModele();

private:
        Modele* modele;
        void threadCall();
        bool partieEnCours;
};

#endif // CONTROLEUR_H
