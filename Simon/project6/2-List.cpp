#include <iostream>
using namespace std;

#include "2-List.h"

#define InvalidObject -1

//Constructor
List::List() {       
    length = 0;
    head = nullptr;
    tail = nullptr;
}

List::List(List& LstIn) : List() {
    node* cur = LstIn.head;
    while (cur != nullptr) {
        PutItemT(cur->item);
        cur = cur->next;
    }
}

//Destructor
List::~List() {
    cout << "Welcome to the Destructor" << endl;
    if (IsEmpty()) return;
    
    node* cur = head;
    while (cur != nullptr) {
        node* next = cur->next;
        delete cur;
        cur = next;
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
}

// 1-based position for user-friendliness.
// Inserts node at a specific position.
void List::InsertItem(int pos, itemType itemIn) {
    // Case 1: Inserting into an empty list.
    // The only valid position is 1.
    if (IsEmpty()) {
        if (pos == 1) {
            PutItemH(itemIn);
        }
        return;
    }

    // Case 2: Inserting at the head of the list.
    if (pos == 1) {
        PutItemH(itemIn);
        return;
    }

    // Case 3: Inserting at the tail of the list.
    if (pos == length + 1) {
        PutItemT(itemIn);
        return;
    }

    // Case 4: Position is out of bounds.
    // As per test case behavior, add to the tail.
    if (pos <= 0 || pos > length) {
        PutItemT(itemIn); 
        return;
    }

    // Case 5: Inserting in the middle of the list.
    node* cur = head;
    // Traverse to the node *before* the insertion point.
    for (int i = 1; i < pos - 1; i++) {
        cur = cur->next;
    }

    node* newNode = new node;
    newNode->item = itemIn;
    newNode->next = cur->next;
    cur->next = newNode;

    length++;
}

bool List::IsEmpty() {
    return length == 0;
}

void List::Print() {
    node* cur = head;
    while(cur != nullptr) {
        cout << cur->item << endl;
        cur = cur->next;
    }
}

int List::GetLength() {
    return length;
}

void List::PutItemH(itemType itemIn) {
    node* newHead = new node;
    newHead->item = itemIn;
    newHead->next = head;

    if (IsEmpty()) {
        tail = newHead;
    }

    head = newHead;
    length++;
}

void List::PutItemT(itemType itemIn) {
    if (IsEmpty()) {
        PutItemH(itemIn);
        return;
    }

    node* newTail = new node;
    newTail->item = itemIn;
    newTail->next = nullptr;

    node* oldTail = tail;
    if (oldTail != nullptr) {
        oldTail->next = newTail;
    }

    tail = newTail;
    length++;
}

itemType List::GetItemH() {
    if (IsEmpty()) return InvalidObject;
    if (head == nullptr) return InvalidObject;

    return head->item;
}

itemType List::GetItemT() {
    if (IsEmpty()) return InvalidObject;
    if (tail == nullptr) return InvalidObject;

    return tail->item;
}

void List::DeleteItemH() {
    if (IsEmpty()) return;

    node* oldHead = head;
    head = head->next;
    delete oldHead;
    length--;

    // If the list is now empty, the tail must also be null.
    if (IsEmpty()) {
        tail = nullptr;
    }
}

void List::DeleteItemT() {
    if (IsEmpty()) return;
    if (head == nullptr) return;
    if (tail == nullptr) return;
    if (length == 1) {
        DeleteItemH();
        return;
    }

    node* cur = head;
    while (cur != nullptr) {
        node* next = cur->next;
        if (next == tail) {
            cur->next = nullptr;
            delete next;
            tail = cur;
            break;
        }
        cur = next;
    }

    length--;
}

int List::Find(itemType target) {
    if (IsEmpty()) return 0;

    int count = 0;
    node* cur = head;
    while (cur != nullptr) {
        if (cur->item == target) {
            count++;
        }
        cur = cur->next;
    }

    return count;
}

int List::DeleteItem(itemType target) {
    if (IsEmpty()) return 0;

    int numDeleted = 0;
    node* prev = nullptr;
    node* cur = head;

    while (cur != nullptr) {
        if (cur->item == target) {
            node* nodeToDelete = cur;
            // Case 1: Deleting the head node
            if (prev == nullptr) { 
                head = cur->next;
                cur = head; // Move to the new head
            } 
            // Case 2: Deleting a middle or tail node
            else {
                prev->next = cur->next;
                cur = cur->next; // Move to the next node
            }

            // If the deleted node was the tail, update the tail pointer
            if (nodeToDelete == tail) {
                tail = prev;
            }

            delete nodeToDelete;
            length--;
            numDeleted++;
        } else {
            // Move to the next node
            prev = cur;
            cur = cur->next;
        }
    }
    return numDeleted;
}