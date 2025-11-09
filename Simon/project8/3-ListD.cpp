#include <iostream>
#include <climits>
using namespace std;

#include "3-ListD.h"

ListD::ListD() {
    InitializeVars();
}

ListD::ListD(ListD* lst) {
    InitializeVars();
    //returns a pointer to the first node, which is what we want here
    doubleNode* cur = lst->FindPosition(2);
    for (int i = 1; i <= lst->length; i++) {
        Insert(cur->item,i);
        cur = cur->next;
    }
}

void ListD::InitializeVars() {
    length = 0;

    //create dummy nodes;
    head = new doubleNode;
    tail = new doubleNode;

    //set values for head dummy node;
    head->prev = nullptr;
    head->item = INT_MIN;
    head->next = tail;

    //set values for tail dummy node;
    tail->prev = head; 
    tail->item = INT_MAX;
    tail->next = nullptr;
}

doubleNode* ListD::FindPosition(int pos) {
    //Inserting at the tail is a special case.  It can be made much more efficient than
    //this.
    //You could also make this more efficient by choosing whether to search from the head or the
    //the tail, depending on where pos is with respect to the middle of the list. 

    doubleNode* cur = head;
    int i = 0;  //begin at the dummy node
    while (i < pos - 1) {
        cur = cur->next;
        i++;
    }
    return cur;
} 

void ListD::Insert(itemType item, int pos) {
    //new node goes between these two nodes
    doubleNode* insertPtA = FindPosition(pos);  
    doubleNode* insertPtB = insertPtA->next; 

    //create new node and set its values
    doubleNode* tmp = new doubleNode; 
    tmp->prev = insertPtA;
    tmp->item = item;
    tmp->next = insertPtB;

    //set pointers for nodes before and after the insertion point
    insertPtA->next = tmp;
    insertPtB->prev = tmp;

    length++;
}

void ListD::PrintForward() {
    if (head == nullptr) return;
    doubleNode* cur = head->next;

    int i = 0;
    while (i < length) {
        cout << cur->item << endl;
        cur = cur->next;
        i++;
    }
}

void ListD::PrintBackward() {
    if (tail == nullptr) return;
    doubleNode* cur = tail->prev;

    int i = length;
    while (i > 0) {
        cout << cur->item << endl;
        cur = cur->prev;
        i--;
    }
}

void ListD::Delete(int pos) {
    if (pos < 1 || pos > length) return;

    doubleNode* nodeToDelete = head->next;
    
    for (int i = 1; i < pos; i++) {
        nodeToDelete = nodeToDelete->next;
    }

    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;

    delete nodeToDelete;
    length--;
}

ListD::~ListD() {
    doubleNode* cur = head;
    doubleNode* tmp;

    while (cur != nullptr) {
        tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

int ListD::DeleteAll(itemType item) {
    int numDeleted = 0;
    doubleNode* cur = head->next;
    int currentPos = 1;
    
    while (cur != tail) {
        if (cur->item == item) {
            cur = cur->next;
            Delete(currentPos);
            numDeleted++;
        } else {
            cur = cur->next;
            currentPos++;
        }
    }

    return numDeleted;
}

void ListD::Sort() {
    if (length <= 1) return;

    doubleNode* current = head->next;
    while (current != tail) {
        doubleNode* minNode = current;
        doubleNode* runner = current->next;
        while (runner != tail) {
            if (runner->item < minNode->item) {
                minNode = runner;
            }
            runner = runner->next;
        }

        if (minNode != current) {
            itemType temp = current->item;
            current->item = minNode->item;
            minNode->item = temp;
        }
        current = current->next;
    }
}
