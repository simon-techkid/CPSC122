#include <iostream>
using namespace std;

#include "1-List.h"

int main() {
    List lst1;
    List* lst2 = new List;

    // Test PutItemH and Print
    cout << "*****Test PutItemH and Print*****" << endl;
    cout << "*****Static Declaration*****" << endl;
    cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
    for (int i = 0; i < 5; i++)
        lst1.PutItemH(i);
    lst1.Print();
    cout << endl;
    // End Test

    // Test PutItemH and Print
    cout << "*****Test PutItemH and Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
    for (int i = 0; i < 5; i++) lst2->PutItemH(i);
    lst2->Print();
    cout << endl;
    // End Test

    // Test GetLength and Print
    cout << "*****Test GetLength, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    lst2->Print();
    cout << "Length (Expected: 5): " << lst2->GetLength() << endl;
    cout << endl;
    // End Test

    // Test Find and Print
    cout << "*****Test Find*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    lst2->Print();
    cout << "Find 4 (Expected: 0): " << lst2->Find(4) << endl;
    cout << "Find 3 (Expected: 1): " << lst2->Find(3) << endl;
    cout << "Find 2 (Expected: 2): " << lst2->Find(2) << endl;
    cout << "Find 1 (Expected: 3): " << lst2->Find(1) << endl;
    cout << "Find 0 (Expected: 4): " << lst2->Find(0) << endl;
    cout << endl;
    // End Test

    // Test PutItemT and Print
    cout << "*****Test PutItemT, Find, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    lst2->PutItemT(12);
    lst2->Print();
    cout << "Find 12 (Expected: 5): " << lst2->Find(12) << endl;
    cout << endl;
    // End Test

    // Test DeleteItemH, Find, and Print
    cout << "*****Test DeleteItemH, Find, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    lst2->DeleteItemH();
    lst2->Print();
    cout << "Find 4 (Expected: -1): " << lst2->Find(4) << endl;
    cout << endl;

    // Test DeleteItemT, Find, and Print
    cout << "*****Test DeleteItemT, Find, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    lst2->DeleteItemT();
    lst2->Print();
    cout << "Find 12 (Expected: -1): " << lst2->Find(12) << endl;
    cout << endl;
    // End Test

    // Test GetItemH, Find, and Print
    cout << "*****Test GetItemH, Find, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    itemType itemH = lst2->GetItemH();
    lst2->Print();
    cout << "Find " << itemH << " (Expected: 0): " << lst2->Find(itemH) << endl;
    cout << endl;
    // End Test

    // Test GetItemT, Find, and Print
    cout << "*****Test GetItemT, Find, Print*****" << endl;
    cout << "*****Dynamic Declaration*****" << endl;
    itemType itemT = lst2->GetItemT();
    lst2->Print();
    cout << "Find " << itemT << " (Expected: 3): " << lst2->Find(itemT) << endl;
    cout << endl;
    // End Test


    //Destructor must be invoked on dynamically declared lists
    delete lst2;
    return 0;
}
