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

List::List(List &LstIn) {
    //Hint: Traverse LstIn. For each node, keep track of the position and the item.
    //Use Inser (InsertItem(int pos,itemType itemIn) to add copy of what you've just read
    //to the list.  If you wrote Insert correctly, it should keep track of the tail pointer

}

//Destructor
List::~List() {
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

void List::InsertItem(int pos, itemType itemIn) {
    if (IsEmpty() && (pos != 0 || pos != length)) return;
    if (pos == 0) {
        PutItemH(itemIn);
        return;
    }
    if (pos == length) {
        PutItemT(itemIn);
        return;
    }

    // Out of Range
    if (pos > length || pos < 0) {
        return;
    }

    length++;
    return;
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
    int len = 0;

    node* cur = head;
    while (cur != nullptr) {
        len++;
        cur = cur->next;
    }
    
    return len;
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
    if (head == nullptr) return;

    node* oldHead = head;
    node* newHead = head->next;
    head = newHead;
    delete oldHead;

    length--;
}

void List::DeleteItemT() {
    if (IsEmpty()) return;
    if (head == nullptr) return;
    if (tail == nullptr) return;

    node* cur = head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }

    node* tailPrecedent = cur;
    node* oldTail = tail;
    if (tailPrecedent->next != tail) {
        cout << "TROUBLE" << endl;
    }
    tailPrecedent->next = nullptr;
    delete oldTail;
    
    length--;
}
