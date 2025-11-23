#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>

//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn) {
    if (argvIn == nullptr) {
        cout << "Error: No expression provided." << endl;
        exit(EXIT_FAILURE);
    }

    int strLen = strlen(argvIn);
    inFixLen = strLen;

    inFix = new char[inFixLen + 1];
    strcpy(inFix, argvIn);

    if (CheckTokens() == false) {
        cout << "Error: Invalid token in expression." << endl;
        exit(EXIT_FAILURE);
    }

    if (CheckParens() == false) {
        cout << "Error: Unbalanced parentheses in expression." << endl;
        exit(EXIT_FAILURE);
    }
    
    MakeValueTbl();

    stk = new Stack();
}

Calc::~Calc() {
    if (inFix != nullptr) {
        delete[] inFix;
        inFix = nullptr;
    }
    if (valueTbl != nullptr) {
        delete[] valueTbl;
        valueTbl = nullptr;
    }
    if (stk != nullptr) {
        delete stk;
        stk = nullptr;
    }
}

// Parentheses
// (ASCII values 40 and 41)
enum PARENTHESES : char {
    LEFT_PAREN = '(',
    RIGHT_PAREN = ')'
};

// Operators
// (ASCII values between 42 and 47)
enum OPERATORS : char {
    MUL = '*',
    ADD = '+',
    SUB = '-',
    DIV = '/'
};

// Digits 0-9
// (ASCII values between 48 and 57)
enum NUMBERS : char {
    ZERO = '0',
    NINE = '9'
};

// Upper case letters A-Z
// (ASCII values between 65 and 90)
enum LETTERS : char {
    A = 'A',
    Z = 'Z'
};

bool Calc::CheckTokens() {
    if (inFix == nullptr) return false;

    for (int i = 0; i < inFixLen; i++) {
        char ch = inFix[i];
        if (!(
            (ch >= OPERATORS::ADD && ch <= OPERATORS::DIV) ||
            (ch >= LETTERS::A && ch <= LETTERS::Z) ||
            (ch >= NUMBERS::ZERO && ch <= NUMBERS::NINE) ||
            (ch == PARENTHESES::LEFT_PAREN || ch == PARENTHESES::RIGHT_PAREN)
        )) {
            return false;
        }
    }

    return true;
}

void Calc::MakeValueTbl() {
    valueTbl = new int[26];
    valueIdx = 0;
    for (int i = 0; i < 26; ++i) {
        valueTbl[i] = 0;
    }
}

void Calc::Parse() {

}

bool Calc::CheckParens() {
    if (inFix == nullptr) return false;

    Stack parenStack;

    for (int i = 0; i < inFixLen; i++) {
        char ch = inFix[i];
        if (ch == PARENTHESES::LEFT_PAREN) {
            // Push left parenthesis onto stack
            parenStack.Push(ch);
        } else if (ch == PARENTHESES::RIGHT_PAREN) {
            if (parenStack.IsEmpty()) {
                // Unmatched right parenthesis
                return false;
            }
            // Pop matching left parenthesis from stack
            parenStack.Pop();
        }
    }

    // If stack is empty, all parentheses are balanced
    return parenStack.IsEmpty();
}

void Calc::DisplayInFix() {
    if (inFix == nullptr) return;
    cout << inFix << endl;
}
