#include <iostream>
using namespace std;

#include "3-ListD.h"

//All tests are controlled by a dedicated function
void TestInsert();
void TestCopyConstructor();
void TestPrintBackward();
void TestDelete();
void TestDeleteAll();
void TestSort();

int main() {
    TestInsert();
    TestCopyConstructor();
    TestPrintBackward();
    TestDelete();
    TestDeleteAll();
    TestSort();
}

typedef int itemType;

template<>
int ListD<int>::GetDefaultHead() {
    return INT_MIN;
}

template<>
int ListD<int>::GetDefaultTail() {
    return INT_MAX;
}

void TestInsert() {
    ListD<itemType>* lst = new ListD<itemType>;
    for (int i = 1; i <= 5; i++)
        lst->Insert(i,i);

    cout << "test general case insert" << endl;
    cout << "Passed Insert Test 1 if 1 through 5 appear on subsequent lines" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "test insert at the head" << endl;
    lst->Insert(0,1);
    cout << "Passed Insert Test 2 if 0 appears in position 1" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "test insert at the tail" << endl;
    lst->Insert(100,7);
    cout << "Passed Insert Test 3 if 100 appears in final position" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "test insert within the list" << endl;
    lst->Insert(50,5);
    cout << "Passed Insert Test 4 if 50 appears in the fifth position" << endl;
    lst->PrintForward();
    cout << endl;
    delete lst;
}

void TestCopyConstructor() {
    ListD<itemType>* lst1 = new ListD<itemType>();
    for (int i = 1; i <= 3; i++)
        lst1->Insert(i,i);

    ListD<itemType>* lst2 = new ListD<itemType>(lst1);

    cout << "Test Copy Constructor" << endl;
    cout << "Test passed if copy is indentical to initial list" << endl;
    cout << "Traverse inital list" << endl;
    lst1->PrintForward();
    cout << endl;
    cout << "Traverse copy" << endl;
    lst2->PrintForward();
    cout << endl;

    delete lst1;
    delete lst2;
}

void TestPrintBackward() {
    ListD<itemType>* lst1 = new ListD<itemType>();
    for (int i = 1; i <= 5; i++) {
        lst1->Insert(i, i);
    }

    cout << "Forward:" << endl;
    lst1->PrintForward();
    cout << "Backward:" << endl;
    lst1->PrintBackward();
    cout << endl;
    delete lst1;
}

void TestDelete() {
    cout << "--- Testing Delete ---" << endl;
    ListD<itemType>* lst = new ListD<itemType>;
    for (int i = 1; i <= 5; i++)
        lst->Insert(i,i);

    cout << "Original list:" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "Deleting from middle (pos 3, item 3):" << endl;
    lst->Delete(3);
    lst->PrintForward();
    cout << endl;

    cout << "Deleting from head (pos 1, item 1):" << endl;
    lst->Delete(1);
    lst->PrintForward();
    cout << endl;

    cout << "Deleting from tail (pos 3, item 5):" << endl;
    lst->Delete(3);
    lst->PrintForward();
    cout << endl;

    delete lst;
}

void TestDeleteAll() {
    cout << "--- Testing DeleteAll ---" << endl;
    ListD<itemType>* lst = new ListD<itemType>;
    lst->Insert(1,1);
    lst->Insert(2,2);
    lst->Insert(1,3);
    lst->Insert(3,4);
    lst->Insert(1,5);

    cout << "Original list with duplicates of 1:" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "Deleting all 1s:" << endl;
    int deletedCount = lst->DeleteAll(1);
    cout << "Deleted " << deletedCount << " items. List should be 2, 3." << endl;
    lst->PrintForward();
    cout << endl;

    cout << "Deleting item not in list (7):" << endl;
    deletedCount = lst->DeleteAll(7);
    cout << "Deleted " << deletedCount << " items. List should be unchanged." << endl;
    lst->PrintForward();
    cout << endl;

    delete lst;
}

void TestSort() {
    cout << "--- Testing Sort ---" << endl;
    ListD<itemType>* lst = new ListD<itemType>;
    lst->Insert(5,1);
    lst->Insert(2,2);
    lst->Insert(8,3);
    lst->Insert(1,4);
    lst->Insert(9,5);

    cout << "Unsorted list:" << endl;
    lst->PrintForward();
    cout << endl;

    cout << "Sorted list (should be 1, 2, 5, 8, 9):" << endl;
    lst->Sort();
    lst->PrintForward();
    cout << endl;

    delete lst;
}
