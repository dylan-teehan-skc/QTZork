#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"

class Parser {
private:
    CommandWords *commands;

public:
    Parser();
    void showCommands();
    Command *getCommand(string buffer);
};

#endif /*PARSER_H_*/
