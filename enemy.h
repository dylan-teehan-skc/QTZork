#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Hostile.h"
#include "Player.h"

class Enemy : public Character, public Hostile {
private:
    int damage;

public:
    Enemy(std::string description, int health, int damage);
    void attack(Player& player);
    void intimidate(Player& player) override;
};

#endif // ENEMY_H