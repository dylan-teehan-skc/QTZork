// processCommand.h

#ifndef PROCESSCOMMAND_H
#define PROCESSCOMMAND_H

#include "ZorkUL.h"

class ZorkUL;

class ProcessCommand {
private:
    ZorkUL* game;

public:
    ProcessCommand(ZorkUL* gamePtr);
    bool processCommand(Command command);
    string go(string direction);
};

#endif // PROCESSCOMMAND_H
