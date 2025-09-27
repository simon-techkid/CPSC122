/*
 Name: Simon Field
 Class: CPSC 122, Section 02
 Date Submitted: September 5, 2025
 Assignment: Project 1
 Description: This program computes prime numbers.
 Sources:
  StackOverflow, 9/5/2025, https://stackoverflow.com/questions/3473438/return-array-in-a-function
  Medium, 9/5/2025, https://medium.com/@joao_vaz/c-iterators-and-implementing-your-own-custom-one-a-primer-72f1506e5d71
  LearnCPP.com, 9/5/2025, https://www.learncpp.com/cpp-tutorial/in-and-out-parameters/
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define USAGE_STRING "Usage: ./project1 <positive_num> <columns>";

// convert command line arguments to integers
void argToInt(int&, int&, char*[]);

// display primes on cout
void display(int&, int&);

// determine if a number is prime
bool is_prime(int);

// determine if a number is even
bool is_even(int);

// class to iterate through the first n prime numbers.
class PrimeIterator {
private:
    int current; // current prime
    int count;   // how many primes have been generated so far
    int maxCount; // total number of primes to generate
public:
    PrimeIterator(int start, int maxCount);
    PrimeIterator(int start, int count, int maxCount); // new constructor for end iterator
    int operator*() const;
    PrimeIterator& operator++();
    bool operator!=(const PrimeIterator& other) const;
};

// a cpp style iterator class to handle iteration with PrimeIterator
class PrimeRange {
    int maxCount;
public:
    PrimeRange(int maxCount);
    PrimeIterator begin() const;
    PrimeIterator end() const;
};

int main(int argc, char* argv[]) {
    // ensure we have provided the correct number of arguments
    if (argc != 3) goto FAILURE_CASE;
    int n;
    int c;
    
    // parse arguments and ensure they can be parsed as valid integers
    try {
        argToInt(n, c, argv);
    } catch (invalid_argument) {
        goto FAILURE_CASE;
    }
    
    // print out the count and columns of primes on cout
    cout << "Number: " + to_string(n) + " Columns: " + to_string(c) << endl;
    
    // display in columns the primes
    display(n, c);

    // success
    return 0;
    FAILURE_CASE:
    // fail case
    const string usageInfo = USAGE_STRING;
    cout << usageInfo << endl;
    return -1;
}

inline void display(int& n, int& c) {
    // create prime range iterator for first n primes
    PrimeRange* ran = new PrimeRange(n + 1);

    // vector to store the primes
    std::vector<int> myVec;

    // iterate through primes and put them in the vector
    for (PrimeIterator it = ran->begin(); it != ran->end(); ++it) {
        myVec.emplace_back(*it);
    }

    // start at the first column
    int currCol = 0;

    // normalize width of columns based on number of primes in the vector
    int width = std::to_string(myVec.empty() ? 0 : myVec.back()).size() + 1;

    // iterate through primes and pad them with the width of the highest prime
    for (int prime : myVec) {
        std::cout << std::setw(width) << prime; // padding
        ++currCol; // column increase
        if (currCol == c) { // terminate column at desired column width
            std::cout << std::endl;
            currCol = 0;
        }
    }
    if (currCol != 0) std::cout << std::endl; // column ends early, print newline at end

    // cleanup the iterator
    delete ran;
}

inline void argToInt(int& n, int& c, char* argv[]) {
    char* arg1 = argv[1]; // pointer to first arg
    char* arg2 = argv[2]; // pointer to second arg
    n = atoi(arg1); // parse number of primes
    c = atoi(arg2); // parse count of columns
    if (n <= 0 || c <= 0) {
        throw invalid_argument("Arguments must be positive integers.");
    }
}

inline bool is_prime(int num) {
    if (num < 2) {
        return false; // numbers less than 2 are not prime
    }
    
    if (is_even(num) && num != 2) { // 2 is the exceptional even prime
        return false; // if even (half of all numbers), exit early to save performance
    }

    for (int i = 3; i * i <= num; i += 2) { // only check odd numbers starting from 3
        if (num % i == 0) {
            return false;
        }
    }

    // not evenly divisible by anything else, true.
    return true;
}

inline bool is_even(int num) {
    return num % 2 == 0;
}

PrimeIterator::PrimeIterator(int start, int maxCount) : current(start), count(0), maxCount(maxCount) {
    while (count < maxCount && !is_prime(current)) ++current;
    if (is_prime(current)) count = 1;
}

PrimeIterator::PrimeIterator(int start, int count, int maxCount) : current(start), count(count), maxCount(maxCount) {}

PrimeIterator& PrimeIterator::operator++() {
    if (count >= maxCount) return *this;
    do {
        ++current;
    } while (!is_prime(current));
    ++count;
    return *this;
}

bool PrimeIterator::operator!=(const PrimeIterator& other) const {
    return count != other.count;
}

int PrimeIterator::operator*() const {
    return current;
}

PrimeRange::PrimeRange(int maxCount) : maxCount(maxCount) {}

PrimeIterator PrimeRange::begin() const {
    return PrimeIterator(2, maxCount);
}

PrimeIterator PrimeRange::end() const {
    return PrimeIterator(0, maxCount, maxCount);
}
