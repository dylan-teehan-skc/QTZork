#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Initialize the singleton instance to nullptr
Player* Player::instance = nullptr;

// Singleton getInstance method
Player* Player::getInstance(string description, int health) {
    if (instance == nullptr) {
        instance = new Player(description, health);
    }
    return instance;
}

// Constructor definition
Player::Player(string description, int health)
: Character(description, health), health(health) {}

// Getter for health
int Player::getHealth() const {
    return health;
}

// Setter for health
void Player::setHealth(int health) {
    this->health = min(max(health, 0), 100);
}

// Specific attack method for attacking an Enemy
void Player::attack(Enemy& enemy) {
    Player *player = Player::getInstance();
    Item equippedWeapon = player->getEquippedWeapon();
    if (equippedWeapon.getDamage() > 0) {
        cout << "Character attacks " << enemy.getDescription() << " with " << equippedWeapon.getName() << " causing "
             << equippedWeapon.getDamage() << " damage." << endl;
        enemy.setHealth(enemy.getHealth() - equippedWeapon.getDamage());
    } else {
        cout << "You can't attack with this weapon, please equip another." << endl;
    }
}
