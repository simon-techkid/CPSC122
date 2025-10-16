#include <iostream>
using namespace std;

#include "1-List.h"

#define InvalidItem -1

//Constructor
List::List() {
    length = 0;
    head = nullptr;
}

//Destructor
List::~List() {
    cout << "I'm in the destructor" << endl;
    node* cur = head;
    while(cur != nullptr) {
        node* next = cur->next;
        delete cur;
        cur = next;
    }
}

void List::PutItemH(itemType itemIn) {
	// Create item to put at the start of the Linked List
    node* tmp = new node;
    tmp->item = itemIn; // Set the new item to the desired item
    tmp->next = head; // New head points to old head
    
    // Set the head to that item
    head = tmp;
    
    length++;
}

itemType List::GetItemH() {
    if (IsEmpty()) return InvalidItem;
    return head->item;
}

void List::DeleteItemH() {
    if (IsEmpty()) return;

    node* tmp = head;
    head = head->next;
    delete tmp;
    
    length--;
}

bool List::IsEmpty() {
    return head == nullptr && length == 0;
}

int List::GetLength() {
    if (IsEmpty()) return 0;

    node* cur = head;
    int index = 0;
    while (cur != nullptr) {
        cur = cur->next;
        index++;
    }
    
    // At this point, index is the length of the list
    return index;
}

void List::Print() {
	if (IsEmpty()) return;

    // Walk through the list, printing each item
    node* cur = head;
    while (cur != nullptr) {
        cout << cur->item << endl;
        cur = cur->next;
    }
}

int List::Find(itemType target) {
    if (IsEmpty()) return InvalidItem;

    // Walk through the list until the item matches the target
    node* cur = head;
    int index = 0;
    while (cur != nullptr) {
        itemType item = cur->item;
        if (item == target) {
            return index;
        }
        index++;
        cur = cur->next;
    }

    return -1;
}

void List::PutItemT(itemType item) {
    // Create item to put at the end of the Linked List
    node* tmp = new node;
    tmp->item = item;
    tmp->next = nullptr;

    // If empty, set the head to the item
    if (IsEmpty()) {
        head = tmp;
    } else { // Otherwise, get the last element
        node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = tmp;
    }

    length++;
}

itemType List::GetItemT() {
    if (IsEmpty()) return InvalidItem;

    // Walk to the end of the list
    node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }

    // At this point, cur is the last item in the list
    return cur->item;
}

void List::DeleteItemT() {
    if (IsEmpty()) return;
    
    // If single-item list, remove the old head.
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else { // Otherwise, get the second-to-last element
        node* cur = head;
        while (cur->next->next != nullptr) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
    }

    length--;
}
