#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(string name, bool hasDamage, int damage)
    : name(name), hasDamage(hasDamage), damage(damage) {}

void Item::setDamage(int inDamage) {
    if (hasDamage) {
        damage = inDamage;
    } else {
        std::cout << "This item does not have damage." << std::endl;
    }
}

int Item::getDamage() const {
    return damage;
}

string Item::getName() const {
    return name;
}

ostream& operator<<(ostream& os, const Item& item) {
    os << "Item: " << item.getName() << ", Damage: " << (item.hasDamage ? to_string(item.damage) : "N/A");
    return os;
}
