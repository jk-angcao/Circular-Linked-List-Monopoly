#ifndef PLAYERFUNCTION_CPP
#define PLAYERFUNCTION_CPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "MonopolyNode.cpp"

using namespace std;

class Player {
    public:
    TrueOwner* owner;
    MonopolyNode* currentPosition;
    bool isBot;
    vector<string> properties;
    bool isBankrupt;

    Player(TrueOwner* truePlayer, MonopolyNode* playerPosition, bool npc = false, bool gameOver = true) {
        owner = truePlayer;
        currentPosition = playerPosition;
        isBot = npc;
        properties = {};
        isBankrupt = gameOver;
    }

    void movePlayer() {
        int roll = rand() % 3 + 1;
        
        cout << owner->ownerName << " rolled a " << roll;
        for (int i = 0; i < roll; i++) {
            currentPosition = currentPosition->next;
            if (currentPosition->name == "Go") {
                owner->money = owner->money + 30;
                cout << ", gained 30 dollars,";
            }
        }
        cout << " and landed on " << currentPosition->name << endl;

        if ((currentPosition->owned == true) && (currentPosition->truestOwner->ownerName != owner->ownerName)) {
            int rent = (currentPosition->cost) / 5;
            payMoneyTo(owner, currentPosition->truestOwner, rent);
        }
    }

    void payMoneyTo(TrueOwner* payer, TrueOwner* recipient, int amount) {
        payer->money = payer->money - amount;
        recipient->money = recipient->money + amount;
        
        cout << payer->ownerName << " paid $" << amount << " to " << recipient->ownerName << endl;
    }

    void buyProperty() {
        owner->money = owner->money - currentPosition->cost;
        currentPosition->owned = true;
        currentPosition->truestOwner = owner;
        properties.push_back(currentPosition->name);
        cout << owner->ownerName << " bought " << currentPosition->name << " for $" << currentPosition->cost << endl;
    }

    void upgradeProperty() {
        owner->money = owner->money - currentPosition->cost - 50;
        currentPosition->cost = currentPosition->cost * 2;
        cout << owner->ownerName << " has upgraded their property! Rent costs double for this property now\n";
    }
};

#endif