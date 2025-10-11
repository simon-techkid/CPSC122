/*
 Name: Simon Field
 Class: CPSC 122, Section 02
 Date Submitted: October 10, 2025
 Assignment: Project 4
 Description: Program illustrates using class MyString.
 Sources:
  CPPReference, 10/9/2025, https://www.cplusplus.com/reference/cstring/?kw=cstring
*/

#include "8-MyString.h"
#include <iostream>
using namespace std;

//usage ./a.out Higgledy
//where "Hiddledy" is input string
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Incorrect number of command line arguments" << endl;
        return 1;
    }
    char* argument = argv[1];
    MyString str1(argument);
    MyString* str2 = new MyString(argument);

    //Test of myDisplay
    /*
    cout << "*****Test myDisplay*****" << endl;
    cout << "static test" << endl;
    cout << "output should be the command line input" << endl;
    str1.myDisplay();
    cout << endl;
    */
    //End Test of myDisplay

    //Test of myStrlen
    /*
    cout << "*****Test myStrlen*****" << endl;
    cout << "dynamic test" << endl;
    cout << "output should be length of command line input" << endl;
    cout << str2->myStrlen() << endl;
    cout << endl;
    */
    //End Test of myStrlen

    //Test of myStrcpy
    /*
    cout << "*****Test myStrcpy*****" << endl;
    cout << "dynamic test" << endl;
    cout << "myStrcpy Initial Value (Expecting \"" << argument << "\"): ";
    str2->myDisplay();

    char testStr1[6] = "Hello";
    str2->myStrcpy(testStr1);
    cout << "myStrcpy Run (Expecting \"Hello\"): ";
    str2->myDisplay();
    
    char testStr2[8] = "Goodbye";
    cout << "myStrcpy Run (Expecting \"Goodbye\"): ";
    str2->myStrcpy(testStr2);
    str2->myDisplay();
    
    cout << endl;
    */
    //End Test of myStrcpy
    
    //Test of isEqual
    /*
    cout << "*****Test isEqual*****" << endl;
    cout << "static test" << endl;

    MyString isEq("hi");
    bool isEqTest1 = !isEq.isEqual("Hi");
    
    isEq.myStrcpy("Hi");
    bool isEqTest2 = isEq.isEqual("Hi");
    
    cout << "isEqual Pass: " << ((isEqTest1 && isEqTest2) ? "yes" : "no") << endl;
    cout << endl;
    */
    //End Test of myStrcpy

    //Test of find
    /*
    cout << "*****Test find*****" << endl;
    cout << "static test" << endl;
    MyString find("The Quick Brown Fox Jumped Over the Lazy Dog");
    char testFind1[6] = "Quick";
    char testFind2[4] = "Fox";
    char testFind3[4] = "Dog";
    char testFind4[6] = "Hello";
    bool test1Pass = find.find(testFind1) == 4;
    bool test2Pass = find.find(testFind2) == 16;
    bool test3Pass = find.find(testFind3) == 41;
    bool test4Pass = find.find(testFind4) == -1;
    bool allPass = test1Pass && test2Pass && test3Pass && test4Pass;
    cout << "find Pass: " << (allPass ? "yes" : "no") << endl;
    cout << endl;
    */
    //End Test of myStrcpy

    //Test of concat
    /*
    cout << "*****Test concat*****" << endl;
    cout << "static test" << endl;
    char testConcat1[6] = "Hello";
    char testConcat2[6] = "World";
    char testConcat3[9] = "Goodbyte";
    char testConcat4[6] = "World";

    MyString testConcatStr(testConcat1);
    cout << "concat Initial Value (Expecting \"Hello\"): ";
    testConcatStr.myDisplay();

    testConcatStr.concat(testConcat2);
    cout << "concat Run (Added \"" << testConcat2 << "\"): ";
    testConcatStr.myDisplay();
    
    testConcatStr.concat(testConcat3);
    cout << "concat Run (Added \"" << testConcat3 << "\"): ";
    testConcatStr.myDisplay();

    testConcatStr.concat(testConcat4);
    cout << "concat Run (Added \"" << testConcat4 << "\"): ";
    testConcatStr.myDisplay();

    cout << endl;
    */
    //End Test of concat

    delete str2;
    return 0;  
}
