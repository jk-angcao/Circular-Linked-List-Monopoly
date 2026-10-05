#ifndef MONOPOLYNODE_CPP
#define MONOPOLYNODE_CPP

#include <iostream>
#include <string>

using namespace std;

/* Used in other file to create Player class. This is here to make it easier to interact
   with the MonopolyMode class and the Player class. There probably was an easier way, but
   I certainly don't know it */
struct TrueOwner {
    string ownerName;
    int money = 500;
};

// Singularly linked list nodes used to store info on property
class MonopolyNode {
    public:
    string name;
    int cost;
    bool owned;
    bool isGo; // Reserved for go space
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

    // Prints out relevent information of a node
    void nodeData() {
        cout << name << ", " << truestOwner->ownerName << ": $" << cost << endl;
    }
};

// Adds various functions to the linked list.
class MonopolyBoard {
    MonopolyNode* head;

    public:

    MonopolyBoard() {
        head = NULL;
    }

    // Appends a node to the end of the list.
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

    // Deletes a node based on the name of Property
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

    // Prints out relevant information from all nodes
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
