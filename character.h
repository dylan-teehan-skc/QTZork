#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Character {
private:
    Item *equippedWeapon;
    string description;
    int health;
    vector<Item> itemsInCharacter;

public:
    Character(string description, int health);

    void addItem(const Item &item);

    string Inventory() const;

    virtual void setHealth(int health);
    virtual int getHealth() const;

    const string &getDescription() const;

    void setDescription(const string &description);

    const vector<Item> &getItemsInCharacter() const;

    virtual void attack(Character &target);

    bool hasItem(const string &itemName) const;

    void equipWeapon(const Item &weapon);

    Item getEquippedWeapon() const;
};

#endif
