#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "Item.h"
#include "processCommand.h"
#include "enemy.h"
#include <iostream>
#include <string>
#include <QSize>

using namespace std;

class ZorkUL {

private:
    void createRooms();
    Parser parser;
    void printWelcome();
    Room *currentRoom;
    ProcessCommand processor = ProcessCommand(nullptr);
    Enemy* enemy;


public:
    ZorkUL();
    void play();
    Room* getCurrentRoom();
    void printHelp();
    bool update(string buffer);
    void goRoom(Command command);
    void checkForBattle();
    void battle(Enemy &enemy);
    void goRoom(Command command, ZorkUL *gamePtr);
    void initiateBattle();
    void processBattleCommand(Command command, ZorkUL &game);
    void processBattleCommand(Command command, ZorkUL *gamePtr);
};

#endif /*ZORKUL_H_*/
