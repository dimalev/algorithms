// chapter games

#include <iostream>
#include <iomanip>

// float precision
void f() {
  std::cout << "size of int: " << sizeof(int) << std::endl
            << "size of float: " << sizeof(float) << std::endl;
  int x = 2100000009;
  float f = x;
  std::cout << x << ' ' << f << std::endl;
  std::cout << std::setprecision(15) << f << std::endl;
}

// char overflow in int representation
void g() {
  char ch = 0;
  for(int i = 0; i < 500; ++i)
    std::cout << int(ch++) << "\t";
  std::cout << std::endl;
}

int main() {
  f();
  g();
  return 0;
}
