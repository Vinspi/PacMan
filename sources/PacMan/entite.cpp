#include "entite.h"

entite::entite(int x, int y)
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
    this->dir[0] = 0;
    this->dir[1] = -1;

    return true;
}

bool entite::MoveDown()
{
    this->dir[0] = 0;
    this->dir[1] = 1;

    return true;
}

bool entite::MoveLeft()
{
    this->dir[0] = -1;
    this->dir[1] = 0;

    return true;
}

bool entite::MoveRight()
{
    this->dir[0] = 1;
    this->dir[1] = 0;

    return true;
}
