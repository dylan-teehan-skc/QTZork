#include <iostream>
#include <fstream>
#include "ZorkUL.h"
#include "json.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Player.h"
#include "processCommand.h"
#include "mainwindow.h"

using json = nlohmann::json;
using namespace std;

//
//int main(int argc, char** argv) {
//    Player* player = Player::getInstance();
//    Enemy enemy("Goblin", 100, 50);
//
//    Item sword("Sword", true, 15);
//    player->addItem(sword);
//    player->equipWeapon(sword);
//    cout << player->getEquippedWeapon();
//
//    cout << player->Inventory() << endl;
//    cout << "Equipped weapon: " << player->getEquippedWeapon() << endl;
//
//    player->attack(enemy);
//    cout << "Enemy health after attack: " << enemy.getHealth() << endl;
//
//    ZorkUL temp(nullptr);
//    temp.play();
//    return 0;
//}


void ZorkUL::createRooms() {

    ifstream ifs("C:/Users/dylan/MyRepos/ZorkNoQt/rooms.json");
    if (!ifs.is_open()) {
        cerr << "Error opening file rooms.json" << endl;
        return;
    }

    json roomsData;
    ifs >> roomsData;

    map<string, Room*> roomMap;

    // Create rooms
    for (const auto& roomData : roomsData["rooms"]) {
        string roomName = roomData["name"];
        string roomDescription = roomData["description"];
        Room* room = new Room(roomName, roomDescription);
        roomMap[roomName] = room;

        for (const auto& itemData : roomData["items"]) {
            string itemName = itemData["name"];
            room->addItem(new Item(itemName));
            bool hasDamage = itemData["hasDamage"];
            if (hasDamage){
                int damage = itemData["damage"];
                room->addItem(new Item(itemName, hasDamage, damage));
            }

        }
    }

    // Set exits
    for (const auto& roomData : roomsData["rooms"]) {
        string roomName = roomData["name"];
        Room* room = roomMap[roomName];

        // Set exits to null by default
        Room* exitN = nullptr;
        Room* exitE = nullptr;
        Room* exitS = nullptr;
        Room* exitW = nullptr;

        // Check if exit directions exist and set corresponding room pointers
        if (roomData.find("exitN") != roomData.end() && !roomData["exitN"].empty()) {
            auto exits = roomData["exitN"];
            if (exits.is_array() && !exits.empty()) {
                string exitRoomName = exits[0];
                exitN = roomMap[exitRoomName];
            }
        }

        if (roomData.find("exitE") != roomData.end() && !roomData["exitE"].empty()) {
            auto exits = roomData["exitE"];
            if (exits.is_array() && !exits.empty()) {
                string exitRoomName = exits[0];
                exitE = roomMap[exitRoomName];
            }
        }

        if (roomData.find("exitS") != roomData.end() && !roomData["exitS"].empty()) {
            auto exits = roomData["exitS"];
            if (exits.is_array() && !exits.empty()) {
                string exitRoomName = exits[0];
                exitS = roomMap[exitRoomName];
            }
        }

        if (roomData.find("exitW") != roomData.end() && !roomData["exitW"].empty()) {
            auto exits = roomData["exitW"];
            if (exits.is_array() && !exits.empty()) {
                string exitRoomName = exits[0];
                exitW = roomMap[exitRoomName];
            }
        }

        // Set exits for the current room
        room->setExits(exitN, exitE, exitS, exitW);
    }
    currentRoom = roomMap["Salty Springs"];
}

Room* ZorkUL::getCurrentRoom() {
    return currentRoom;
}

ZorkUL::ZorkUL(ZorkUL *pUl) : processor(this){
    createRooms();
}

void ZorkUL::play() {
    printWelcome();
    createRooms();
}

bool ZorkUL::update(string buffer) {
    // Create pointer to command and give it a command.
    Command* command = parser.getCommand(buffer);
    // Check if command is null before processing
    if (command == nullptr) {
        // Free the memory allocated by "parser.getCommand()"
        delete command;
        return false; // Indicate that the command was not processed
    }

    // Pass dereferenced command and check for end of game.
    bool finished = processor.processCommand(*command); // Call processCommand on the processor
    // Free the memory allocated by "parser.getCommand()"
    delete command;
    return finished;
}

void ZorkUL::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;

}

























/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
/*
 bool ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
        cout << "invalid input"<< endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
    {
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
    }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("pickup") == 0)
    {
        if (!command.hasSecondWord()) {
            cout << "incomplete input"<< endl;
        }
        else if (command.hasSecondWord()) {
            cout << "you're trying to take " + command.getSecondWord() << endl;
            int location = currentRoom->isItemInRoom(command.getSecondWord());
            if (location  < 0 )
                cout << "item is not in room" << endl;
            else
                cout << "item is in room" << endl;
            cout << "index number " << + location << endl;

            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            cout << "overdefined input"<< endl;
        else
            return true; // signal to quit
    }
    return false;
}

void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
    }
}

string ZorkUL::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}
*/