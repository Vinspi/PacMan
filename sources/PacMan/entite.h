#ifndef ENTITE_H
#define ENTITE_H

#include "const.h"

class entite
{
    enum DIRECTION {reculer = -1, stop = 0, avancer = 1};

    protected:
        //Position dans la fenetre
        int px_x;
        int px_y;

        //Position dans le graphe
        int gr_x;
        int gr_y;

        // Direction de l'entité
        // dir[0] : x
        // dir[1] : y
        DIRECTION dir[2];

        // Rectangle de collision
        QRect collision;

    public:
        //Constructeur
        entite(int x, int y);

        //Fonctions de déplacement
        // (juste la direction)
        bool MoveUp();
        bool MoveDown();
        bool MoveLeft();
        bool MoveRight();

        //Getter
        int GetPX_X();
        int GetPX_Y();
        int GetGR_X();
        int GetGR_Y();
        int GetDir();
        QRect GetCol();

        //Setter
        void SetX(int x);
        void SetY(int y);
        void SetCol(QRect c);
};

#endif // ENTITE_H
