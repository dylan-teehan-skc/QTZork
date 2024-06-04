#include "ZorkUL.h"
#include "processCommand.h"
#include "Player.h"
#include "mainwindow.h"
#include "enemy.h"

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
    } else if (commandWord.compare("map") == 0) {
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
                QString itemString = QString::fromStdString("You picked up a " + itemName + " from the room");
                MainWindow::getInstance()->append(itemString);
                cout << "You picked up a " << itemName << " from the room." << endl;
            }
        }
    } else if (commandWord.compare("equip") == 0) {
        string itemName = command.getSecondWord();
        if (!command.hasSecondWord()) {
            MainWindow::getInstance()->append("Incomplete input");
            cout << "Incomplete input" << endl;
        } else if (player->hasItem(itemName)) {
            // Find the item in the player's inventory
            const vector<Item> &playerItems = player->getItemsInCharacter();
            for (const Item &item: playerItems) {
                if (item.getName() == itemName) {
                    // Equip the item
                    player->equipWeapon(item);
                    QString equippedString = QString::fromStdString("You have equipped " + itemName);
                    MainWindow::getInstance()->append(equippedString);
                    cout << "You have equipped " << itemName << endl;
                    break; // Exit the loop once the item is equipped
                }
            }
        } else {
            MainWindow::getInstance()->append("You do not have this item");
            cout << "You do not have this item" << endl;
        }
    } else if (commandWord.compare("equipped?") == 0) {
        cout << player->getEquippedWeapon();
    } else if (commandWord.compare("health") == 0) {
        QString healthString = QString::fromStdString("Your health is " + player->getHealth());
        MainWindow::getInstance()->append(healthString);
        cout << "Your health is " << player->getHealth() << endl;
    } else if (commandWord.compare("use") == 0) {
        string itemName = command.getSecondWord();
        if (!command.hasSecondWord()) {
            MainWindow::getInstance()->append("incomplete input");
            cout << "incomplete input" << endl;
        } else {
            if (itemName == "Key" && player->hasItem(itemName)) {
                MainWindow::getInstance()->append("You open a rusty closet to find a Shotgun on the ground");
                cout << "You open a rusty closet to find a shotgun on the ground" << endl;
                game->getCurrentRoom()->addItem(new Item("Shotgun", "True", 30));
            } else if (itemName == "Bandages" && player->hasItem(itemName)) {
                player->setHealth(player->getHealth() + 50);
                QString healthUpdateString = QString::fromStdString(
                        "Your health is has been updated to" + player->getHealth());
                MainWindow::getInstance()->append(healthUpdateString);
                cout << "Your health has been updated to " << player->getHealth() << endl;
            } else if (player->hasItem(itemName)) {
                MainWindow::getInstance()->append("You cannot use this item");
            } else {
                MainWindow::getInstance()->append("You have not picked up this item yet");
                cout << "You have not picked up this item yet" << endl;
            }
        }

    } else if (commandWord.compare("put") == 0) {

    } else if (commandWord.compare("inventory") == 0) {
        QString inventoryString = QString::fromStdString(player->Inventory());
        MainWindow::getInstance()->append(inventoryString);
        cout << player->Inventory() << endl;
    } else if (commandWord.compare("room?") == 0) {
        QString roomString = QString::fromStdString(game->getCurrentRoom()->longDescription());
        MainWindow::getInstance()->append(roomString);
        cout << game->getCurrentRoom()->longDescription();
    } else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord()) {
            MainWindow::getInstance()->append("overdefined input");
            cout << "overdefined input" << endl;
        } else
            return true;
    }
    return false;

}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        MainWindow::getInstance()->append("Incomplete input");
        cout << "incomplete input" << endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room *nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL) {
        MainWindow::getInstance()->append("You cannot go this direction");
        cout << "underdefined input" << endl;
    } else {
        currentRoom = nextRoom;
        QString descriptionString = QString::fromStdString(currentRoom->longDescription());
        MainWindow::getInstance()->append(descriptionString);
        cout << currentRoom->longDescription() << endl;

    }
}


void ZorkUL::checkForBattle() {
    // 20% chance of a battle
    if (rand() % 100 < 99) {
        // Generate a random enemy
        string enemyName = "Goblin"; // You can use a random name generator
        int enemyHealth = 100; // Randomize health
        int enemyAttack = 50; // Randomize attack

        Enemy enemy(enemyName, enemyHealth, enemyAttack);

        // Start the battle
        battle(enemy);
    }
}

void ZorkUL::battle(Enemy& enemy) {

    // Inform the user that a battle has started
    QString enemyString = QString::fromStdString("A wild " + enemy.getDescription() + " appears!");
    MainWindow::getInstance()->append(enemyString);

    // Perform battle logic
    while (player->getHealth() > 0 && enemy.getHealth() > 0) {
        // Player attacks first
        player->attack(enemy);

        // Check if enemy is defeated
        if (enemy.getHealth() <= 0) {
            QString enemyDefeatString = QString::fromStdString("You defeated the " + enemy.getDescription() + "!");
            MainWindow::getInstance()->append(enemyDefeatString);
            break;
        }

        // Enemy attacks
        enemy.attack(*player);

        // Check if player is defeated
        if (player->getHealth() <= 0) {
            QString playerDefeatString = QString::fromStdString("You were defeated by the " + enemy.getDescription() + "...");
            MainWindow::getInstance()->append(playerDefeatString);
            break;
        }
    }
}
