#include <iostream>
using namespace std;

#include "calc.h"
#include "list.h"
#include <cstring>

#define VALUE_TABLE_SIZE 26
#define TEST false

//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn) {
    if (argvIn == nullptr) {
        cout << "Error: No expression provided." << endl;
        exit(EXIT_FAILURE);
    }

    inFix = new char[strlen(argvIn) + 1];
    strcpy(inFix, argvIn);

    if (!CheckTokens()) {
        cout << "Error: Invalid token in expression." << endl;
        exit(EXIT_FAILURE);
    }

    if (!CheckParens()) {
        cout << "Error: Unbalanced parentheses in expression." << endl;
        exit(EXIT_FAILURE);
    }
    
    if (TEST) DisplayInFix();

    MakeValueTbl();
    Parse();

    if (TEST) DisplayInFix();

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

bool Calc::CheckTokens() {
    if (inFix == nullptr) return false;

    for (int i = 0; i < inFixLen; i++) {
        char ch = inFix[i];
        if (!(
            (ch >= OPERATORS::MUL) ||
            (ch == OPERATORS::ADD) ||
            (ch == OPERATORS::SUB) ||
            (ch == OPERATORS::DIV) ||
            (ch == PARENTHESES::LEFT_PAREN) ||
            (ch == PARENTHESES::RIGHT_PAREN) ||
            (isalpha(ch) && isupper(ch)) ||
            (isdigit(ch))
        )) {
            return false;
        }
    }

    return true;
}

void Calc::MakeValueTbl() {
    valueTbl = new int[VALUE_TABLE_SIZE];
    valueIdx = 0;
    for (int i = 0; i < VALUE_TABLE_SIZE; ++i) {
        valueTbl[i] = 0;
    }
}

void Calc::Parse() {
    if (inFix == nullptr) return;

    char* items = new char[inFixLen + 1];
    int itemsIdx = 0;

    for (int i = 0; i < inFixLen; ) {
        char ch = inFix[i];

        if (ch < NUMBERS::ZERO || ch > NUMBERS::NINE) {
            items[itemsIdx++] = ch;
            i++;
            continue;
        }

        char* endPtr;
        int value = strtol(&inFix[i], &endPtr, 10);
        int length = endPtr - &inFix[i];
        
        valueTbl[valueIdx] = value;
        char varChar = 'A' + valueIdx;
        items[itemsIdx++] = varChar;
        valueIdx++;
        
        i += length;
    }
    items[itemsIdx] = '\0'; // Null-terminate the new string

    if (TEST) {
        cout << items << endl;

        for (int i = 0; i < valueIdx; i++) {
            char varChar = 'A' + i;
            cout << varChar << ": " << valueTbl[i] << endl;
        }
        cout << endl;
    }

    delete[] inFix;
    inFix = items;
    inFixLen = itemsIdx;

    return;
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
