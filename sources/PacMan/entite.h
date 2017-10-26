#ifndef ENTITE_H
#define ENTITE_H

class entite
{
    protected:
        //Position dans la fenetre
        int px_x;
        int px_y;

        //Position dans le graphe
        int gr_x;
        int gr_y;

        // Direction de l'entité
        // dir[0] : x = {-1, 0, 1}
        // dir[1] : y = {-1, 0, 1}
        int dir[2];

    public:
        //Constructeur
        entite(int x, int y);

        //Fonctions de déplacement
        // (juste la direction pour le moment)
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

        //Setter
        void SetX(int x);
        void SetY(int y);
};

#endif // ENTITE_H
