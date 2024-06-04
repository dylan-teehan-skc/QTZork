#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "Character.h" // Include necessary headers

// Enemy class declaration
class Enemy : public Character {
private:
    int damage;

public:
    Enemy(string description, int health, int damage);
    virtual
    void attack(Player &player);
};

#endif // ENEMY_H
