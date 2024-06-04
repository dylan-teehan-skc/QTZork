#include <iostream>
#include <fstream>
#include "ZorkUL.h"
#include "json.hpp"
#include "Player.h"
#include "mainwindow.h"

using json = nlohmann::json;
using namespace std;

class FileOpenException : public exception {
private:
    std::string message;

public:
    FileOpenException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

void ZorkUL::createRooms() {

    ifstream ifs("C:/Users/dylan/MyRepos/ZorkWithQt/rooms.json");
    if (!ifs.is_open()) {
        throw FileOpenException("file could not be opened");
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
            bool hasDamage = itemData["hasDamage"];
            if (hasDamage){
                int damage = itemData["damage"];
                room->addItem(new Item(itemName, hasDamage, damage));
            }
            else{
                room->addItem(new Item(itemName));
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

ZorkUL::ZorkUL() : processor(this){
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
    cout << endl;
    cout << currentRoom->longDescription() << endl;

}

void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();
}

void ZorkUL::initiateBattle() {
    string enemyName = "Goblin"; 
    int enemyHealth = 100; 
    int enemyAttack = 5;

    enemy = new Enemy(enemyName, enemyHealth, enemyAttack); 
    
    QString enemyString = QString::fromStdString("A wild " + enemy->getDescription() + " appears!");
    MainWindow::getInstance()->append(enemyString);
}


void ZorkUL::processBattleCommand(Command command, ZorkUL *gamePtr) {
    Player *player = Player::getInstance();
    string commandWord = command.getCommandWord();

    if (commandWord.compare("attack") == 0) {
        player->attack(*enemy);
        if (enemy->getHealth() <= 0) {
            QString enemyDefeatString = QString::fromStdString("You defeated the " + enemy->getDescription() + "!, He drops a prestiege Crown");
            MainWindow::getInstance()->append(enemyDefeatString);
            gamePtr->getCurrentRoom()->addItem(new Item("Crown"));
            delete enemy;
            enemy = nullptr;
            return;
        }
    } else if (commandWord.compare("block") == 0) {
        // Block logic: player takes no damage this turn
        QString blockString = "You block the enemy's attack!";
        MainWindow::getInstance()->append(blockString);
        enemy->intimidate(*player);
    } else {
        MainWindow::getInstance()->append("Invalid command during battle!");
        cout << "Invalid command during battle!" << endl;
        return;
    }

    // Enemy attacks unless player blocked
    if (commandWord.compare("block") != 0) {
        enemy->attack(*player);
    }

    // Check if player is defeated
    if (player->getHealth() <= 0) {
        QString playerDefeatString = QString::fromStdString("You were defeated by the " + enemy->getDescription() + "...");
        QString gameOverString = QString::fromStdString("Game is now over");
        MainWindow::getInstance()->append(playerDefeatString);
        MainWindow::getInstance()->append(gameOverString);
        delete enemy;
        enemy = nullptr;
    }
}



