#ifndef PACMAN_H
#define PACMAN_H
#include "entity.h"

class PacMan : public Entity
{
public:
    PacMan();
    int moveIsLegal();
};

#endif // PACMAN_H
