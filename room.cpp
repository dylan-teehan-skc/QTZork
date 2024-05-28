#include "Room.h"
#include "Command.h"

Room::Room(string name, string description) {
    this->description = description;
    this->name = name;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

string Room::shortDescription() {
    return description;
}

string Room::longDescription() {
    return description + "\n" + displayItem() + exitString();
}

string Room::exitString() {
    string returnString = "\nexits =";
    for (map<string, Room *>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;    // access the "first" element of the pair (direction as a string)
    return returnString;
}

Room *Room::nextRoom(string direction) {
    map<string, Room *>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
}

void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
    } else if (itemsInRoom.size() > 0) {
        int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getName() + "  ";
            x++;
        }
    }
    return tempString;
}

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString) {
    int sizeItems = itemsInRoom.size();
    if (sizeItems < 1) {
        return -1; // Return -1 to indicate no items in the room
    } else {
        for (int x = 0; x < sizeItems; x++) {
            // Compare inString with short description
            if (inString == itemsInRoom[x].getName()) {
                return x; // Return the index of the found item
            }
        }
    }
    return -1; // Return -1 if item not found
}


const Item *const Room::getItem(int index) const {
    if (index >= 0 && index < itemsInRoom.size()) {
        return &itemsInRoom[index];
    } else {
        return nullptr;
    }
}


