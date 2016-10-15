// print size of primitive types using `sizeof`

#include <iostream>
#include <typeinfo>
#include <string>

template<typename T>
void printSize(const std::string msg = "") {
  if(!msg.empty()) std::cout << "type " << msg << "(" << typeid(T).name() << ")";
  else std::cout << "type " << typeid(T).name();
  std::cout << " size = " << sizeof(T) << std::endl;
}

int main() {
  printSize<char>();
  printSize<short>();
  printSize<int>();
  printSize<unsigned int>("unsigned int");
  printSize<long>();
  printSize<unsigned long>("unsigned long");
  printSize<float>();
  printSize<double>();
  printSize<long double>();
  printSize<int*>();
  printSize<double*>();
  printSize<size_t>("size_t");
  printSize<ptrdiff_t>("ptrdiff_t");
  return 0;
}
