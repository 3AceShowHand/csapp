#include <iostream>
using namespace std;


int main() {

  int a = 5;
  int& ref = a;

  cout << "address of a is " << &a << endl;
  cout << "address of ref is " << &ref <<endl;

  // reference and const
  int x = 5;
  const int &ref1 = x;
  cout << "ref1 is " << ref1 << endl;
  x += 1;
  cout << "ref1 is " << ref1 << endl;

  return 0;
}
