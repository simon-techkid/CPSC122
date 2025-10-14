#include <iostream>
using namespace std;

#include "1-List.h"

int main() {
    List lst1;
    List* lst2 = new List;

    // Test PutItemH and Print
    cout << "Static Declaration" << endl;
    cout << "Test PutItemH and Print" << endl;
    cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
    for (int i = 0; i < 5; i++)
        lst1.PutItemH(i);
    lst1.Print();
    cout << endl;
    // End Test

    // Test GetLength
    cout << "Length: " << lst1.GetLength() << endl;
    cout << endl;
    // End Test

    // Test PutItemH and Print
    cout << "Dynamic Declaration" << endl;
    cout << "Test PutItemH and Print" << endl;
    cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
    for (int i = 0; i < 5; i++)
        lst2->PutItemH(i);
    lst2->Print();
    cout << endl;
    // End Test

    // Test GetLength
    cout << "Length: " << lst2->GetLength() << endl;
    cout << endl;
    // End Test

    // Test Find and Print
    cout << "Find 4 (Expected: 0): " << lst2->Find(4) << endl;
    cout << "Find 3 (Expected: 1): " << lst2->Find(3) << endl;
    cout << "Find 2 (Expected: 2): " << lst2->Find(2) << endl;
    cout << "Find 1 (Expected: 3): " << lst2->Find(1) << endl;
    cout << "Find 0 (Expected: 4): " << lst2->Find(0) << endl;
    cout << endl;
    // End Test

    // Test PutItemT and Print
    lst2->PutItemT(12);
    cout << "Find 12 (Expected: 5): " << lst2->Find(12) << endl;
    lst2->Print();
    cout << endl;
    // End Test

    // Test DeleteItemH, Find, and Print
    lst2->DeleteItemT();
    cout << "Find 12 (Expected: -1): " << lst2->Find(12) << endl;
    cout << endl;
    // End Test

    //Destructor must be invoked on dynamically declared lists
    delete lst2;
    return 0;
}
