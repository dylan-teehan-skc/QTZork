#include "CommandWords.h"

vector<string> CommandWords::validCommands;

/**
 * Constructor - initialise the command words.
 */
CommandWords::CommandWords() {
    // Populate the vector if we haven't already.
    if (validCommands.empty()) {
        validCommands.push_back("go");
        validCommands.push_back("quit");
        validCommands.push_back("info");
        validCommands.push_back("Map");
        validCommands.push_back("pickup");
        validCommands.push_back("put");
        validCommands.push_back("room?");
        validCommands.push_back("inventory");
        validCommands.push_back("use");
        validCommands.push_back("health");
        validCommands.push_back("equip");
        validCommands.push_back("equipped?");
        validCommands.push_back("battle");
        validCommands.push_back("attack");
        validCommands.push_back("block");
    }
}

/**
 * Check whether a given String is a valid command word.
 * Return true if it is, false if it isn't.
 **/
bool CommandWords::isCommand(string aString) {
    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        if (validCommands[i].compare(aString) == 0)
            return true;
    }
    // if we get here, the string was not found in the commands
    return false;
}

/*
 * Print all valid commands to System.out.
 */
void CommandWords::showAll() {
    //Loops through validCommands and prints each to the screen.
    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        cout << validCommands[i]<< "  ";
    }
    cout << endl;
}
