#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "mainwindow.h"
#include <iostream>
#include <algorithm>
#include <qstring.h>
#include <sstream>

using namespace std;

Player* Player::instance = nullptr;

struct PlayerFlags {
    unsigned int isAlive : 1;
    unsigned int isDefending : 1;
    unsigned int isAttacking : 1;
    unsigned int isMoving : 1;
};

// Singleton getInstance method
Player* Player::getInstance(string description, int health) {
    if (instance == nullptr) {
        instance = new Player(description, health);
    }
    return instance;
}

// Constructor definition
Player::Player(string description, int health)
: Character(description, health), health(health) {
    make_unique<PlayerFlags>()->isAlive=1;
    make_unique<PlayerFlags>()->isDefending=0;
    make_unique<PlayerFlags>()->isAttacking=0;
    make_unique<PlayerFlags>()->isMoving=0;
}

// Getter for health
int Player::getHealth() const {
    return health;
}

// Setter for health
void Player::setHealth(int health) {
    this->health = min(max(health, 0), 100);
}

void Player::attack(Enemy& enemy) {
    Player *player = Player::getInstance();
    Item equippedWeapon = player->getEquippedWeapon();
    if (equippedWeapon.getDamage() > 0) {
        enemy.setHealth(enemy.getHealth() - equippedWeapon.getDamage());
        std::stringstream playerAttackString;
        playerAttackString << "Player attacks " << enemy.getDescription() << " with " << equippedWeapon.getName() << " causing "
                           << equippedWeapon.getDamage() << " damage, enemies health is now " << enemy.getHealth();
        MainWindow::getInstance()->append(QString::fromStdString(playerAttackString.str()));
    } else {
        cout << "You can't attack with this weapon, please equip another." << endl;
    }
}
