#ifndef MONOPOLYNODE_CPP
#define MONOPOLYNODE_CPP

#include <iostream>
#include <string>

using namespace std;

struct TrueOwner {
    string ownerName;
    int money = 500;
};

class MonopolyNode {
    public:
    string name;
    int cost;
    bool owned;
    bool isGo; //reserved for go space
    MonopolyNode* next;
    TrueOwner* truestOwner;

    MonopolyNode(string propertyName, int propertyCost, bool isOwned = false, MonopolyNode* nextNode = nullptr, TrueOwner* testOwner = nullptr, bool noTouchy = false) {
        name = propertyName;
        cost = propertyCost;
        owned = isOwned;
        next = nextNode;
        truestOwner = testOwner;
        isGo = noTouchy;
    }

    void nodeData() {
        cout << name << ", " << truestOwner->ownerName << ": $" << cost << endl;
    }
};

class MonopolyBoard {
    MonopolyNode* head;

    public:

    MonopolyBoard() {
        head = NULL;
    }

    void appendNode(string propertyName, int propertyCost, int propertyOwner = 0, TrueOwner* testOwner = nullptr) {
        MonopolyNode* newNode = new MonopolyNode(propertyName, propertyCost, propertyOwner, nullptr, testOwner);
        if (head == NULL) {
            head = newNode;
            newNode->next = head; // Circular linked list
        }
        else {
            MonopolyNode* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head; // Circular linked list
        }
    }

    void deleteNode(string propertyName) {
        if (head == NULL) {
            return;
        }

        if (head->name == propertyName) {
            if (head->next == head) {
                delete head;
                head = NULL;
                return;
            }
            else {
                MonopolyNode* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                temp->next = head->next;
                delete head;
                head = temp->next;
                return;
            }
        }
        
        MonopolyNode* temp = head;
        do {
            if (temp->next->name == propertyName) {
                MonopolyNode* nodeToDelete = temp->next;
                temp->next = nodeToDelete->next;
                delete nodeToDelete;
                return;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Node does not exist" << endl;
    }

    MonopolyNode* findNode(string propertyName) {
        MonopolyNode* temp = head;
        do {
            if (temp->name == propertyName) {
                return temp;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Node does not exist" << endl;
        return nullptr;
    }


    void boardInformation() {
        head->nodeData();
        MonopolyNode* temp = head->next;
        while (temp != head) {
            temp->nodeData();
            temp = temp->next;
        }
    }

};

#endif