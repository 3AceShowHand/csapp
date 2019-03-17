#include <iostream>

using namespace std;

const char* getName() {
    return "Alex";
}


int main() {
    const char* name = getName();
    cout << name << endl;

    char c = 'Q';
    cout << "c is : " << &c << endl;

    return 0;
}
