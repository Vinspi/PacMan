#ifndef JOUEUR_H
#define JOUEUR_H

#include "entite.h"

class joueur : public entite
{
    private:
        int buffer_event;

    public:
        joueur(int x, int y);
        bool Move(int Event);

        int GetBuffer();
        void SetBuffer(int e);
};

#endif // JOUEUR_H
