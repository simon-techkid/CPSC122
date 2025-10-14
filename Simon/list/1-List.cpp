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
    node* tmp = new node;
    tmp->item = itemIn;
    tmp->next = head;
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
    node* next = head->next;
    head = next;
    delete tmp;
    length--;
}

bool List::IsEmpty() {
    return head == nullptr;
}

int List::GetLength() {
    if (IsEmpty()) return 0;

    node* cur = head;
    int len = 0;
    while (cur != nullptr) {
        cur = cur->next;
        len++;
    }
    return len;
}

void List::Print()
{
    node* cur = head;
    while (cur != nullptr) {
        cout << cur->item << endl;
        cur = cur->next;
    }
}

int List::Find(itemType target) {
    if (IsEmpty()) return InvalidItem;

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
    node* tmp = new node;
    tmp->item = item;
    tmp->next = nullptr;

    node* cur = head;
    while(cur->next != nullptr) {
        cur = cur->next;
    }

    cur->next = tmp;
    length++;
}

itemType List::GetItemT() {
    if (IsEmpty()) return InvalidItem;

    node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    return cur->item;
}

void List::DeleteItemT() {
    node* cur = head;
    while(cur->next->next != nullptr) {
        cur = cur->next;
    }

    node* tmp = cur->next;
    cur->next = nullptr;
    delete tmp;
}