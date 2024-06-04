// processCommand.h

#ifndef PROCESSCOMMAND_H
#define PROCESSCOMMAND_H

#include "ZorkUL.h"
#include "enemy.h"

class ZorkUL;

class ProcessCommand {
private:
    ZorkUL* game;

public:
    ProcessCommand(ZorkUL* gamePtr);
    bool processCommand(Command command);

};

#endif // PROCESSCOMMAND_H
