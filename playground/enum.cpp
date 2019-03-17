#include <iostream>

int main() {
  enum Color {
    RED,
    BLUE
  };

  enum Fruit {
    BANANA,
    APPLE
  };
  
  Color color = RED;
  Fruit fruit = BANANA;

  if (color == fruit) {
     std::cout << "color and fruit are equal\n";
  } else {
     std::cout << "color and fruit are not equal\n";
  }
  
  return 0;

}
