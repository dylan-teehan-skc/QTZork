#ifndef HOSTILE_H
#define HOSTILE_H

#include "Player.h"

class Hostile {
public:
    Hostile();
    virtual void intimidate(Player& player) = 0;
};

#endif
