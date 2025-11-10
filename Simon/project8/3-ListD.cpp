#include <iostream>

using namespace std;

#include "3-ListD.h"

template<typename itemType>
ListD<itemType>::ListD() {
    InitializeVars();
}

template<typename itemType>
ListD<itemType>::ListD(ListD<itemType>* lst) {
    InitializeVars();
    //returns a pointer to the first node, which is what we want here
    doubleNode<itemType>* cur = lst->FindPosition(2);
    for (int i = 1; i <= lst->length; i++) {
        Insert(cur->item,i);
        cur = cur->next;
    }
}

template<typename itemType>
void ListD<itemType>::InitializeVars() {
    length = 0;

    //create dummy nodes;
    head = new doubleNode<itemType>;
    tail = new doubleNode<itemType>;

    //set values for head dummy node;
    head->prev = nullptr;
    head->item = GetDefaultHead();
    head->next = tail;

    //set values for tail dummy node;
    tail->prev = head;
    tail->item = GetDefaultTail();
    tail->next = nullptr;
}

template<typename itemType>
doubleNode<itemType>* ListD<itemType>::FindPosition(int pos) {
    //Inserting at the tail is a special case.  It can be made much more efficient than
    //this.
    //You could also make this more efficient by choosing whether to search from the head or the
    //the tail, depending on where pos is with respect to the middle of the list.

    doubleNode<itemType>* cur = head;
    int i = 0;  //begin at the dummy node
    while (i < pos - 1) {
        cur = cur->next;
        i++;
    }
    return cur;
}

template<typename itemType>
void ListD<itemType>::Insert(itemType item, int pos) {
    //new node goes between these two nodes
    doubleNode<itemType>* insertPtA = FindPosition(pos);
    doubleNode<itemType>* insertPtB = insertPtA->next;

    //create new node and set its values
    doubleNode<itemType>* tmp = new doubleNode<itemType>;
    tmp->prev = insertPtA;
    tmp->item = item;
    tmp->next = insertPtB;

    //set pointers for nodes before and after the insertion point
    insertPtA->next = tmp;
    insertPtB->prev = tmp;

    length++;
}

template<typename itemType>
void ListD<itemType>::PrintForward() {
    if (head == nullptr) return;
    doubleNode<itemType>* cur = head->next;

    int i = 0;
    while (i < length) {
        cout << cur->item << endl;
        cur = cur->next;
        i++;
    }
}

template<typename itemType>
void ListD<itemType>::PrintBackward() {
    if (tail == nullptr) return;
    doubleNode<itemType>* cur = tail->prev;

    int i = length;
    while (i > 0) {
        cout << cur->item << endl;
        cur = cur->prev;
        i--;
    }
}

template<typename itemType>
void ListD<itemType>::Delete(int pos) {
    if (pos < 1 || pos > length) return;

    doubleNode<itemType>* nodeToDelete = head->next;

    for (int i = 1; i < pos; i++) {
        nodeToDelete = nodeToDelete->next;
    }

    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;

    delete nodeToDelete;
    length--;
}

template<typename itemType>
ListD<itemType>::~ListD() {
    doubleNode<itemType>* cur = head;
    doubleNode<itemType>* tmp;

    while (cur != nullptr) {
        tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

template<typename itemType>
int ListD<itemType>::DeleteAll(itemType item) {
    int numDeleted = 0;
    doubleNode<itemType>* cur = head->next;
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

template<typename itemType>
void ListD<itemType>::Sort() {
    if (length <= 1) return;

    doubleNode<itemType>* current = head->next;
    while (current != tail) {
        doubleNode<itemType>* minNode = current;
        doubleNode<itemType>* runner = current->next;
        while (runner != tail) {
            if (*runner < *minNode) {
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

template class ListD<int>;
