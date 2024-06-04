#include <qstring.h>
#include <sstream>
#include "Enemy.h"
#include "Character.h"
#include "Player.h"
#include "mainwindow.h"

using namespace std;

Enemy::Enemy(string description, int health, int damage) : Character(description, health) {
    this->damage = damage;
}

void Enemy::attack(Player& player) { // Pass player by reference
    int damageInflicted = damage;

    player.setHealth(player.getHealth() - damageInflicted);
    cout << "The enemy attacks you for " << damageInflicted << " damage!" << endl;
    std::stringstream attackString;
    attackString << "The enemy attacks you for " << damageInflicted << " damage, your health is now " << player.getHealth();
    MainWindow::getInstance()->append(QString::fromStdString(attackString.str()));
}

void Enemy::intimidate(Player& player) {
    std::stringstream intimidateString;
    intimidateString << "The enemy laughs at you instead! Your health is " << player.getHealth();
    MainWindow::getInstance()->append(QString::fromStdString(intimidateString.str()));
}