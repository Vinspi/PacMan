#include "entite.h"

// collision à changer
entite::entite(int x, int y) : collision(x, y, ENTITE_SIZE, ENTITE_SIZE)
{
    this->x = x;
    this->y = y;
    this->dir[0] = 0;
    this->dir[1] = 0;
}

int entite::GetPX_X()
{
    return this->px_x;
}
int entite::GetPX_Y()
{
    return this->px_y;
}
int entite::GetGR_X()
{
    return this->gr_x;
}
int entite::GetGR_Y()
{
    return this->gr_y;
}
int entite::GetDir()
{
    return this->dir;
}

void entite::SetX(int x)
{
    this->x = x;
}
void entite::SetY(int y)
{
    this->y = y;
}

bool entite::MoveUp()
{
    this->dir[0] = stop;
    this->dir[1] = reculer;

    return true;
}

bool entite::MoveDown()
{
    this->dir[0] = stop;
    this->dir[1] = avancer;

    return true;
}

bool entite::MoveLeft()
{
    this->dir[0] = reculer;
    this->dir[1] = stop;

    return true;
}

bool entite::MoveRight()
{
    this->dir[0] = avancer;
    this->dir[1] = stop;

    return true;
}
