#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "Item.h"
#include "processCommand.h"
#include <iostream>
#include <string>
#include <QSize>

using namespace std;

class ZorkUL {

private:
    void createRooms();
    Parser parser;
    void printWelcome();
    void createItems();
    void displayItems();
    Room *currentRoom;
    ProcessCommand processor = ProcessCommand(nullptr);

public:
    ZorkUL(ZorkUL *pUl);
    void play();
    Room* getCurrentRoom();
    void printHelp();
    void goRoom(Command command);
    string go(string direction);
    bool update(string buffer);
};

#endif /*ZORKUL_H_*/
