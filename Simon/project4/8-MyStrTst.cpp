/*
Name: Paul De Palma
Class: CPSC 122, Section 1
Date Submitted: 9/22/2025
Assignment: N/A 
Description: Program illustrates using class MyString 
*/

#include "8-MyStr.h"
#include <iostream>
using namespace std;

//usage ./a.out Higgledy
//where "Hiddledy" is input string
int main(int argc, char* argv[]) {
    MyString str1(argv[1]);
    MyString* str2 = new MyString(argv[1]);

    //Test of myDisplay
    cout << "*****Test myDisplay*****" << endl;
    cout << "static test" << endl;
    cout << "output should be the command line input" << endl;
    str1.myDisplay();
    cout << endl;
    //End Test of myDisplay

    //Test of myStrlen
    cout << "*****Test myStrlen*****" << endl;
    cout << "dynamic test" << endl;
    cout << "output should be length of command line input" << endl;
    cout << str2->myStrlen() << endl;
    cout << endl;
    //End Test of myStrlen

    //Test of myStrcpy
    cout << "*****Test myStrcpy*****" << endl;
    str2->myDisplay();
    char testStr1[6] = "Hello";
    str2->myStrcpy(testStr1);
    str2->myDisplay();
    char testStr2[8] = "Goodbye";
    str2->myStrcpy(testStr2);
    str2->myDisplay();
    cout << endl;
    //End Test of myStrcpy
    
    //Test of isEqual
    cout << "*****Test isEqual*****" << endl;
    MyString isEq("hi");
    bool isEqTest1 = !isEq.isEqual("Hi");
    isEq.myStrcpy("Hi");
    bool isEqTest2 = isEq.isEqual("Hi");
    cout << "isEqual Pass: " << (isEqTest1 && isEqTest2) << endl;
    cout << endl;
    //End Test of myStrcpy

    //Test of find
    cout << "*****Test find*****" << endl;
    MyString find("The Quick Brown Fox Jumped Over the Lazy Dog");
    bool test1Pass = find.find("Quick") == 4;
    bool test2Pass = find.find("Fox") == 16;
    bool test3Pass = find.find("Dog") == 41;
    bool test4Pass = find.find("Hello") == -1;
    cout << "find Pass: " << (test1Pass && test2Pass && test3Pass && test4Pass) << endl;
    cout << endl;
    //End Test of myStrcpy

    //Test of concat
    cout << "*****Test concat*****" << endl;
    MyString concat("Hello");
    concat.myDisplay();
    concat.concat("Simon");
    concat.myDisplay();
    cout << concat.myStrlen();
    cout << endl;
    //End Test of concat

    delete str2;
    return 0;  
}
