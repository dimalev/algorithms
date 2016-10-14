// print size of primitive types using `sizeof`

#include <iostream>
#include <typeinfo>

template<typename T>
void printSize() {
  std::cout << "type " << typeid(T).name() << " size = " << sizeof(T) << std::endl;
}

int main() {
  printSize<char>();
  printSize<short>();
  printSize<int>();
  printSize<long>();
  printSize<float>();
  printSize<double>();
  printSize<long double>();
  printSize<int*>();
  printSize<double*>();
  return 0;
}
