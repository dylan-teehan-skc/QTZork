#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
using namespace std;

class Item {
protected:
    std::string name;
    bool hasDamage;
    int damage;

public:
    Item(std::string name, bool hasDamage = false, int damage = 0);

    void setDamage(int inDamage);

    int getDamage() const;

    std::string getName() const;

    friend ostream& operator<<(ostream& os, const Item& item);
};

#endif // ITEM_H
