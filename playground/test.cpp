#include <iostream>

using namespace std;


int main() {

  int value = 5;
  const int* ptr = &value;
  cout<< "*ptr is " << *ptr << endl;

  value = 6;
  cout << "*ptr is " << *ptr << endl;

  int c = 1;
  ptr = &c;
  cout << "*ptr is " << *ptr << endl;

  // this should throw error.
  // *ptr += 1;
  // cout << "*ptr is " << *ptr << endl;

  return 0;
}
