#include <iostream>
using namespace std;

#include "2-List.h"

int main()
{
	List lst1;
	List* lst2 = new List;

	// ----- Test PutItemH and Print -----
	cout << "*****Test PutItemH and Print*****" << endl;
	cout << "Static Declaration" << endl;
	cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
	for (int i = 0; i < 5; i++) {
		lst1.PutItemH(i);
	}
	lst1.Print();
	cout << endl;
	// ----- End Test -----
	
	// ----- Test PutItemH and Print -----
	cout << "*****Test PutItemH and Print*****" << endl;
	cout << "Dynamic Declaration" << endl;
	cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
	for (int i = 0; i < 5; i++) {
		lst2->PutItemH(i);
	}
	lst2->Print();
	cout << endl;
	// ----- End Test -----

	// ----- Test Copy Constructor and Print -----
	List* lst3 = new List(*lst2);
	cout << "*****Test Copy Constructor and Print*****" << endl;
	lst2->Print();
	cout << "Matches:" << endl;
	lst3->Print();
	
	delete lst2;
	delete lst3;
	lst2 = nullptr;
	lst3 = nullptr;
	
	cout << endl;
	// ----- End Test -----

	// ----- Test IsEmpty and GetLength -----
	cout << "*****Test IsEmpty and GetLength*****" << endl;
	List lst4;
	cout << "New list. IsEmpty() (1): " << lst4.IsEmpty() << endl;
	cout << "GetLength() (0): " << lst4.GetLength() << endl;
	lst4.PutItemH(10);
	cout << "After PutItemH. IsEmpty() (0): " << lst4.IsEmpty() << endl; 
	cout << "GetLength() (1): " << lst4.GetLength() << endl;
	lst4.DeleteItemH();
	cout << "After DeleteItemH. IsEmpty() (1): " << lst4.IsEmpty() << endl; 
	cout << "GetLength() (0): " << lst4.GetLength() << endl;
	cout << endl;
	// ----- End Test -----

	// ----- Test PutItemH and GetItemH -----
	cout << "*****Test PutItemH and GetItemH*****" << endl;
	List lst5;
	lst5.PutItemH(20);
	lst5.PutItemH(30);
	cout << "List:" << endl;
	lst5.Print();
	cout << "GetItemH() (30): " << lst5.GetItemH() << endl;
	lst5.DeleteItemH();
	cout << "After DeleteItemH. GetItemH() (20): " << lst5.GetItemH() << endl;
	cout << "List:" << endl;
	lst5.Print();
	cout << endl;
	// ----- End Test -----

	// ----- Test PutItemT and GetItemT -----
	cout << "*****Test PutItemT and GetItemT*****" << endl;
	List lst6;
	lst6.PutItemT(100);
	lst6.PutItemT(200);
	lst6.PutItemT(300);
	cout << "List (100, 200, 300): " << endl;
	lst6.Print();
	cout << "GetItemT() (300): " << lst6.GetItemT() << endl;
	cout << endl;
	// ----- End Test -----

	// ----- Test DeleteItemT -----
	cout << "*****Test DeleteItemT*****" << endl;
	cout << "List before deleting tail (100, 200, 300): " << endl;
	lst6.Print();
	lst6.DeleteItemT();
	cout << "List after deleting tail (100, 200): " << endl;
	lst6.Print();
	lst6.DeleteItemT();
	cout << "List after deleting tail again (100): " << endl;
	lst6.Print();
	lst6.DeleteItemT();
	cout << "List after deleting last item (): " << endl;
	lst6.Print();
	cout << "IsEmpty() (1): " << lst6.IsEmpty() << endl;
	cout << endl;
	// ----- End Test -----

	// ----- Test InsertItem -----
	cout << "*****Test InsertItem*****" << endl;
	List lst7;
	lst7.InsertItem(1, 10); // Insert into empty list
	cout << "List (10): " << endl;
	lst7.Print();
	lst7.InsertItem(1, 5); // Insert at head
	cout << "List (5, 10): " << endl;
	lst7.Print();
	lst7.InsertItem(3, 20); // Insert at tail
	cout << "List (5, 10, 20): " << endl;
	lst7.Print();
	lst7.InsertItem(2, 7); // Insert in middle
	cout << "List (5, 7, 10, 20): " << endl;
	lst7.Print();
	lst7.InsertItem(10, 99); // Insert out of bounds (should be at tail)
	cout << "List (5, 7, 10, 20, 99): " << endl;
	lst7.Print();
	cout << endl;
	// ----- End Test -----

	// ----- Test Find -----
	cout << "*****Test Find*****" << endl;
	cout << "List:" << endl;
	lst7.Print();
	cout << "Find 10 (1): " << lst7.Find(10) << endl;
	cout << "Find 99 (1): " << lst7.Find(99) << endl;
	cout << "Find 100 (0): " << lst7.Find(100) << endl;
	lst7.PutItemH(10);
	cout << "List:" << endl;
	lst7.Print();
	cout << "Find 10 (2): " << lst7.Find(10) << endl;
	cout << endl;
	// ----- End Test -----

	// ----- Test DeleteItem -----
	cout << "*****Test DeleteItem*****" << endl;
	List lst8;
	lst8.PutItemH(5);
	lst8.PutItemH(10);
	lst8.PutItemH(5);
	lst8.PutItemH(15);
	lst8.PutItemH(5);
	cout << "List before delete (5, 15, 5, 10, 5): " << endl;
	lst8.Print();
	cout << "Deleting 5s. Items deleted (3): " << lst8.DeleteItem(5) << endl;
	cout << "List after delete (15, 10):" << endl;
	lst8.Print();
	cout << "Deleting 10. Items deleted (1): " << lst8.DeleteItem(10) << endl;
	cout << "List after delete (15):" << endl;
	lst8.Print();
	cout << "Deleting 15. Items deleted (1): " << lst8.DeleteItem(15) << endl;
	cout << "List after delete ():" << endl;
	lst8.Print();
	cout << "IsEmpty() (1): " << lst8.IsEmpty() << endl;
	cout << endl;
	// ----- End Test -----

	// ----- Test Copy Constructor (List*) -----
	cout << "*****Test Copy Constructor (List*)*****" << endl;
	List* lst9 = new List();
	lst9->PutItemH(1);
	lst9->PutItemH(2);
	lst9->PutItemH(3);
	
	List* lst10 = new List(*lst9);
	cout << "Original list:" << endl;
	lst9->Print();
	cout << "Copied list:" << endl;
	lst10->Print();
	cout << "Copied list after deleting original:" << endl;
	lst10->Print();
	cout << endl;

	delete lst9;
	delete lst10;
	// ----- End Test -----

	return 0;
}
