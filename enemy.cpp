#include "Enemy.h"
#include "Character.h"
#include "Player.h"
using namespace std;

Enemy::Enemy(string description, int health, int damage) : Character(description, health) {
    this->damage = damage;
}

void Enemy::attack(Player player) {
    // Retrieve the player character's health
    int playerHealth = Player::getInstance()->getHealth();
    int damageInflicted = damage;

    // Deduct the damage from the player character's health
    playerHealth -= damageInflicted;
    player.setHealth(playerHealth);

    // Print a message indicating the attack action
    cout << "The enemy attacks you for " << damageInflicted << " damage!" << endl;
}

