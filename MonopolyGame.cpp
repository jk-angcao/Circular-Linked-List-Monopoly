#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "MonopolyNode.cpp"
#include "PlayerFunctions.cpp"

using namespace std;

// Using a vector of basic Player constructs, we let players pick out their names and turn the rest into bots with abysmal ai
void playerCreation(int realPlayers, int botPlayers, vector<Player>& characters){
    string name;

    for (int i = 0; i < realPlayers; i++) {
        cout << "Enter name for Player " << (i + 1) << " (No spaces)\n";
        cin >> name;

        characters[i].owner->ownerName = name;
        characters[i].isBankrupt = false;
    }
    for (int i = 0; i < botPlayers; i++) {
        name = "Bot_" + to_string(i + 1);
        characters[i + realPlayers].owner->ownerName = name;
        characters[i + realPlayers].isBot = true;
        characters[i + realPlayers].isBankrupt = false;
    }
}

// Checks to see if all but one player is bankrupt. If so, then game over
bool gameWon(vector<Player>& daList) {
    int bankruptCheck = 0;
    for (Player person : daList) {
        if (person.isBankrupt == true) {
            ++bankruptCheck;
        }
    }

    if (bankruptCheck != 3) {
        return false;
    }

    for(Player person : daList) {
        if (person.isBankrupt == false) {
            cout << person.owner->ownerName << " has won the game!";
            return true;
        }
    }
}

// Boots a player from the game if they have no money
void checkBankruptcy(Player& player, vector<Player>& daList) {
    if (player.owner->money < 1) {
        player.isBankrupt = true;
        cout << player.owner->ownerName << " became bankrupt! Take their shoes! (They are now out of the game)\n";
    }
}

// Prints out relevent info on a specfic player
void findPlayerInfo(vector<Player>& daList) {
    cout << "Type name of player you'd like information of.\n";
    string name;
    cin >> name;

    for (int i = 0; i < daList.size(); i++) {
        if (daList[i].owner->ownerName == name) {
            cout << "Money: " << daList[i].owner->money << 
            " | Location: " << daList[i].currentPosition->name << 
            " | Properties: <";
            
            for (string properties : daList[i].properties) {
                cout << properties << ">, <";
            }
            cout << ">\n\n";
        }
    }
}

// Options for players to choose from when it's their turn
void playerActions(Player& player, vector<Player>& daList) {
    cout << "Actions: Player Locations [L], Player Information [I], Buy/Upgrade Property [P], End Turn [E]\n";
        vector<char> inputs = {'L', 'I', 'P', 'E'};
        char inputAction = 'A';
        cin >> inputAction;

        while ((inputAction != 'L') && (inputAction != 'I') && (inputAction != 'P') && (inputAction != 'E')) {
            cout << "Input not Accepted. Type [L], [I], [P], or [E]\n";
            cin >> inputAction;
        }

        switch (inputAction) {
            case 'L': // Checks specified player's location
                for (Player person : daList) {
                    cout << person.owner->ownerName << " is at " << person.currentPosition->name << " | ";
                }
                cout << endl << endl;
                break;
            case 'I': // Finds relevent player info
                findPlayerInfo(daList);
                break;
            case 'P': // Ends turn after either: buying current property if not owned by anyone; upgrading current property if turn player owns it; or it calls you stupid
                if ((player.currentPosition->owned) == false) {
                player.buyProperty();
                } else if (player.currentPosition->truestOwner->ownerName == player.owner->ownerName) {
                    player.upgradeProperty();
                } else {
                    cout << "You can't buy other people's property, silly.\n";
                }
                checkBankruptcy(player, daList);
                return;
            case 'E': // Ends turn swiftly
                return;
        }
        playerActions(player, daList); // Puts player back into options if the chosen option didn't end the turn
}

// Gives options to turn player. Live players are sent to action menu. Bots automatically purchase/upgrade
void turnActions(Player& player, vector<Player>& daList, int& turnNum) {
    if (player.isBankrupt == true) {
        return;
    }
    cout << "[Turn " << turnNum << ": " << player.owner->ownerName << "'s turn!]\n";
    ++turnNum;

    player.movePlayer();
        
    if (player.isBot == false) {
        playerActions(player, daList);
    } else if ((player.currentPosition->owned == false)) {
        player.buyProperty();
    } else if (player.owner->ownerName == player.currentPosition->truestOwner->ownerName) {
        player.upgradeProperty();
    }
    checkBankruptcy(player, daList);

    cout << endl;
    return;
}

int main() {
    srand(time(0));
    
    // Create Monopoly board and the properties
    MonopolyBoard board;
    board.appendNode("Go", 0, -1);
    board.appendNode("First_Avenue", 60);
    board.appendNode("Second_Avenue", 60);
    board.appendNode("Third_Avenue", 100);
    board.appendNode("Fourth_Avenue", 100);
    board.appendNode("First_Lane", 80);
    board.appendNode("Second_Lane", 80);
    board.appendNode("Third_Lane", 120);
    board.appendNode("Fourth_Lane", 120);
    board.appendNode("First_Street", 100);
    board.appendNode("Second_Street", 100);
    board.appendNode("Third_Street", 140);
    board.appendNode("Fourth_Street", 140);
    board.appendNode("First_Boulevard", 120);
    board.appendNode("Second_Boulevard", 120);
    board.appendNode("Third_Boulevard", 160);
    board.appendNode("Fourth_Boulevard", 160);

    // Creates Playable "chracters"
    TrueOwner first;
    TrueOwner second;
    TrueOwner third;
    TrueOwner fourth;
    Player player1(&first, board.findNode("Go"));
    Player player2(&second, board.findNode("Go"));
    Player player3(&third, board.findNode("Go"));
    Player player4(&fourth, board.findNode("Go"));
    vector<Player> allPlayers = {player1, player2, player3, player4};

    int playerAmount = -1;
    int botAmount = -1;

    // Determines amount of live players
    cout << "How many real players will play? [Enter number from 1-4]" << endl;
    cin >> playerAmount;
    while ((playerAmount < 1) || (playerAmount > 4)) {
        cout << "Invalid Input. [Enter a number from 1-4]\n";
        cin >>playerAmount;
    } 
    cout << "You have selected [" << playerAmount << "] \n";

    // Determines amount of bots
    switch (playerAmount) {
        case 1:
            cout << "How many bots will be played? [Enter number from 1 to 3]\n";
            cin >> botAmount;
            while ((botAmount < 1) || (botAmount > 3)) {
                cout << "Invalid Input. [Enter a number from 1-3]\n";
                cin >> botAmount;
            }
            break;
        case 4:
            botAmount = 0;
            break;
        default:
            cout << "How many bots will be played? [Enter number from 0 to " << 4 - playerAmount << "]\n";
            cin >> botAmount;
            while ((botAmount < 0) || (botAmount > (4 - playerAmount))) {
                cout << "Invalid Input. [Enter a number from 0-" << (4 - playerAmount) << "]\n";
                cin >> botAmount;
            }
            break;
    }
    cout << botAmount << " bots will be playing.\n\n";

    playerCreation(playerAmount, botAmount, allPlayers);

    int playerTurn = 0;
    int turnCount = 1;

    // Starts game. Game continues until all but one person is bankcrupt
    cout << "\nGame Start!\n\n";
    while (gameWon(allPlayers) == false) {
        turnActions(allPlayers[playerTurn % 4], allPlayers, turnCount);
        ++playerTurn;
    }
}
