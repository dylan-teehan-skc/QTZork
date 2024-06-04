#include "Character.h"

Character::Character(string description, int health) {
    this->description = description;
    this->health = health;
}

string Character::shortDescription() {
    return description;
}

void Character::addItem(const Item &item) {
    itemsInCharacter.push_back(item);
}

string Character::Inventory() const {
    string ret = description;
    ret += "\n Item list:\n";
    for (const Item &item: itemsInCharacter) {
        if (item.getDamage() == 0) {
            ret += "\t" + item.getName();
        } else {
            ret += "\t" + item.getName() + ": " + to_string(item.getDamage()) + " damage";
        }
    }
    return ret;
}

void Character::setHealth(int health) {
    Character::health = health;
}

int Character::getHealth() const {
    return health;
}

const string &Character::getDescription() const {
    return description;
}

void Character::setDescription(const string &description) {
    Character::description = description;
}

const vector<Item> &Character::getItemsInCharacter() const {
    return itemsInCharacter;
}

void Character::setItemsInCharacter(const vector<Item> &itemsInCharacter) {
    Character::itemsInCharacter = itemsInCharacter;
}

bool Character::hasItem(const string &itemName) const {
    for (const Item &item: itemsInCharacter) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

void Character::equipWeapon(const Item &weapon) {
    equippedWeapon = new Item(weapon);
}


void Character::attack(Character &target) {
    cout << "Character attacks" << endl;
}

Item Character::getEquippedWeapon() const {
    if (equippedWeapon != nullptr) {
        return *equippedWeapon;
    } else {
        // Return a default constructed Item or handle the no-weapon case
        return Item("No weapon", 0);
    }
}
