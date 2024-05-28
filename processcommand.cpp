#include "ZorkUL.h"
#include "processCommand.h"
#include "Player.h"
#include "mainwindow.h"

Player *player = Player::getInstance();
ProcessCommand::ProcessCommand(ZorkUL *gamePtr) : game(gamePtr) {
}

bool ProcessCommand::processCommand(Command command) {
    if (command.isUnknown()) {
        MainWindow::getInstance()->append("invalid input");
        cout << "invalid input" << endl;

        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0) {
        game->printHelp();
    }

    else if (commandWord.compare("map") == 0) {
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
    } else if (commandWord.compare("go") == 0)
        game->goRoom(command);

    else if (commandWord.compare("pickup") == 0) {
        if (!command.hasSecondWord()) {
            MainWindow::getInstance()->append("incomplete input");
            cout << "incomplete input" << endl;
        } else {
            string itemName = command.getSecondWord();
            int location = game->getCurrentRoom()->isItemInRoom(itemName);
            if (location < 0) {
                MainWindow::getInstance()->append("item is not in room");
                cout << "item is not in room" << endl;
            } else {
                // Get the item from the room
                Item *item = const_cast<Item *>(game->getCurrentRoom()->getItem(location));
                player->addItem(*item);
                QString Item = QString::fromStdString("You picked up a " + itemName + " from the room");
                MainWindow::getInstance()->append(Item);
                cout << "You picked up a " << itemName << " from the room." << endl;
            }
        }
    }

    else if (commandWord.compare("equip") == 0) {
        string itemName = command.getSecondWord();
        if (!command.hasSecondWord()) {
            MainWindow::getInstance()->append("Incomplete input");
            cout << "Incomplete input" << endl;
        } else if (player->hasItem(itemName)) {
            // Find the item in the player's inventory
            const vector<Item>& playerItems = player->getItemsInCharacter();
            for (const Item& item : playerItems) {
                if (item.getName() == itemName) {
                    // Equip the item
                    player->equipWeapon(item);
                    QString equipped = QString::fromStdString("You have equipped " + itemName);
                    MainWindow::getInstance()->append(equipped);
                    cout << "You have equipped " << itemName << endl;
                    break; // Exit the loop once the item is equipped
                }
            }
        } else {
            MainWindow::getInstance()->append("You do not have this item");
            cout << "You do not have this item" << endl;
        }
    }


    else if (commandWord.compare("equipped?") == 0){
        cout << player->getEquippedWeapon();
    }


    else if (commandWord.compare("health") == 0){
        QString health = QString::fromStdString("Your health is " + player->getHealth());
        MainWindow::getInstance()->append(health);
        cout << "Your health is " << player->getHealth() << endl;
    }

    else if (commandWord.compare("use") == 0) {
        string itemName = command.getSecondWord();
        if (!command.hasSecondWord()) {
            MainWindow::getInstance()->append("incomplete input");
            cout << "incomplete input" << endl;
        } else {
            if (itemName == "key" && player->hasItem(itemName)) {
                MainWindow::getInstance()->append("You open a rusty closet to find a shotgun on the ground");
                cout << "You open a rusty closet to find a shotgun on the ground" << endl;
                game->getCurrentRoom()->addItem(new Item("shotgun","True", 30));
            }
            else if(itemName == "bandages" && player->hasItem(itemName)) {
                player->setHealth(player->getHealth()+50);
                QString healthUpdate = QString::fromStdString("Your health is has been updated to" + player->getHealth());
                MainWindow::getInstance()->append(healthUpdate);
                cout << "Your health has been updated to " << player->getHealth() << endl;

            }
            else{
                MainWindow::getInstance()->append( "You have not picked up this item yet");
                cout << "You have not picked up this item yet" << endl;
            }
        }

    } else if (commandWord.compare("put") == 0) {

    } else if (commandWord.compare("inventory") == 0) {
        QString inventory = QString::fromStdString(player->Inventory());
        MainWindow::getInstance()->append(inventory);
        cout << player->Inventory() << endl;
    } else if (commandWord.compare("room?") == 0) {
        QString room = QString::fromStdString(game->getCurrentRoom()->longDescription());
        MainWindow::getInstance()->append(room);
        cout << game->getCurrentRoom()->longDescription();
    } else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
        {MainWindow::getInstance()->append("overdefined input");
            cout << "overdefined input" << endl;}
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
        MainWindow::getInstance()->append( "Incomplete input");
        cout << "incomplete input" << endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room *nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL){
        MainWindow::getInstance()->append( "You cannot go this direction");
        cout << "underdefined input" << endl;}
    else {
        currentRoom = nextRoom;
        QString Description = QString::fromStdString(currentRoom->longDescription());
        MainWindow::getInstance()->append(Description);
        cout << currentRoom->longDescription() << endl;
    }
}

