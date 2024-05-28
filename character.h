#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Character {
private:
    Item* equippedWeapon;
    string description;
    int health;
    vector<Item> itemsInCharacter;

public:
    // Constructor
    Character(string description, int health);

    // Function to return a short description of the character
    string shortDescription() const;

    // Add an item to the character's inventory
    void addItem(const Item &item);

    // Get a formatted inventory string
    std::string Inventory() const;

    virtual // Setter and getter for health
        void setHealth(int health);

    virtual int getHealth() const;

    // Getter and setter for description
    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    // Getter and setter for itemsInCharacter
    const std::vector<Item> &getItemsInCharacter() const;

    void setItemsInCharacter(const std::vector<Item> &itemsInCharacter);

    virtual void attack(Character& target);

    string shortDescription();

    bool hasItem(const string &itemName) const;

    void equipWeapon(const Item& weapon);

    Item getEquippedWeapon() const;
};

#endif /* CHARACTER_H */
