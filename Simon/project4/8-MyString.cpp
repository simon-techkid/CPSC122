#include <iostream>
using namespace std;

#define NULL_TERMINATOR '\0'

#include "8-MyString.h"

MyString::MyString(char const* strIn) {
    int length = myStrLen(strIn);
    str = new char[length + 1];
    int i = 0;
    while (i < length) {
        str[i] = strIn[i];
        i++;
    }
    str[i] = NULL_TERMINATOR;
}

MyString::~MyString() {
    delete []str; 
}

void MyString::myDisplay() {
    cout << str << endl;
}

int MyString::myStrLen(char const* strIn) {
    if (strIn == nullptr) return 0;

    int idx = 0;
    while (strIn[idx] != NULL_TERMINATOR)
    idx++;
    return idx;
}

int MyString::myStrlen() {
    return myStrLen(str);
}

void MyString::myStrcpy(char const* strIn) {
    if (strIn == nullptr) return;
    if (strIn == str) return;

    int lenIn = myStrLen(strIn);
    char* newStr = new char[lenIn + 1];
    
    int index = 0;
    while (index < lenIn) {
        newStr[index] = strIn[index];
        index++;
    }
    newStr[index] = NULL_TERMINATOR;

    char* oldStr = str;
    str = newStr;
    delete []oldStr;
}

bool MyString::isEqual(char const* strIn) {
    if (strIn == nullptr) return false;
    if (strIn == str) return true;

    int lenThis = myStrlen();
    int lenThat = myStrLen(strIn);
    if (lenThis != lenThat) return false;

    for (int i = 0; i < lenThis; i++) {
        if (str[i] != strIn[i]) return false;
    }

    return true;
}

bool MyString::isSub(char const* strIn, int idx) {
    if (strIn == nullptr) return false;
    if (strIn == str) return true;

    int lenThis = myStrlen();
    int lenThat = myStrLen(strIn);
    int adjustment = idx + lenThat;
    if (adjustment > lenThis) return false;

    for (
        int idxThis = idx, idxThat = 0;
        idxThat < lenThat;
        idxThis++, idxThat++) {
        if (str[idxThis] != strIn[idxThat]) {
            return false;
        }
    }

    return true;
}

int MyString::find(char const* strIn) {
    if (strIn == nullptr) return -1;
    if (myStrLen(strIn) == 0) return 0;

    int lenThis = myStrlen();
    int lenThat = myStrLen(strIn);
    if (lenThat == 0) return -1;

    for (int i = 0; i < lenThis; i++) {
        if (str[i] == strIn[0]) {
            if (isSub(strIn, i)) {
                return i;
            }
        }
    }

    return -1;
}

void MyString::concat(char const* strIn) {
    if (strIn == nullptr) return;

    int lenThis = myStrlen();
    int lenThat = myStrLen(strIn);
    if (lenThat == 0) return;

    int totalLength = lenThis + lenThat + 1;
    char* newArr = new char[totalLength];

    for (int i = 0; i < lenThis; i++) {
        newArr[i] = str[i];
    }

    for (int i = 0; i < lenThat; i++) {
        newArr[lenThis + i] = strIn[i];
    }

    newArr[lenThis + lenThat] = NULL_TERMINATOR;

    char* tmp = str;
    str = newArr;
    delete tmp;
}