#include <iostream>
using namespace std;

#include "2-List.h"

int main()
{
	List lst1;
	List* lst2 = new List;

	//This is example Test code
	cout << "*****Test PutItemH and Print*****" << endl;
	cout << "Static Declaration" << endl;
	cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
	for (int i = 0; i < 5; i++) {
		lst1.PutItemH(i);
	}
	lst1.Print();
	cout << endl;
	
	cout << "*****Test PutItemH and Print*****" << endl;
	cout << "Dynamic Declaration" << endl;
	cout << "Correct if output is 4, 3, 2, 1, 0 on subsequent lines" << endl;
	for (int i = 0; i < 5; i++) {
		lst2->PutItemH(i);
	}
	lst2->Print();
	cout << endl;
	
	delete lst2;
	lst2 = new List;
	
	cout << "*****Test PutItemT and Print*****" << endl;
	cout << "Dynamic Declaration" << endl;
	lst2->PutItemT(12);
	lst2->PutItemT(42);
	
	lst2->InsertItem(0, 10);
	lst2->InsertItem(3, 100);
	lst2->Print();
	//lst2->DeleteItemT();

	/*
	10,
	12,
	42,
	

	*/
	lst2->Print();
	cout << endl;

	//Destructor must be invoked for dynamically declared classes
	delete lst2;

	cout << endl;
	return 0;
}
