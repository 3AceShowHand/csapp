#include <iostream>

using namespace std;

int main() {
   
    const int a = 0;
    const int b = 1;
    
    // p is a pointer to const int
    const int* p = &a;
    p = &b;
    
    // t is a const pointer, always point to a int, should throw error, if not initialized or point to a const int.
    int c;    
    int* const t = &c;


    return 0;
}
