#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int* num = new int;
    cout << *num << endl;
    *num = 42;
    cout << *num << endl;
    delete num;
    
    return 0;
}