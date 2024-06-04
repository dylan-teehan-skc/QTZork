#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
class Enemy;

class Player : public Character {
private:
    int health; // Private member variable for health
    static Player *instance; // Static instance variable for singleton pattern
    Player(string description, int health);

public:
    // Static method to get the instance of the player (singleton pattern)
    static Player *getInstance(string description = "Player", int health = 100);
    int getHealth() const;
    void setHealth(int health);
    virtual
    void attack(Enemy& enemy);
};

#endif
