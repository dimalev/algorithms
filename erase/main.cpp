#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
  std::vector<int> data;
  int size, x, a, b;
  std::cin >> size;
  // std::cout << size << std::endl;
  data.resize(size);
  for(int i = 0; i < size; ++i) std::cin >> data[i];
  std::cin >> x;
  std::cin >> a >> b;
  if(x < a) {
    --a; --b;
    data.erase(data.begin() + x - 1, data.begin() + x);
  } else if(x > b) {
    data.erase(data.begin() + x - 1, data.begin() + x);
  }
  data.erase(data.begin() + a - 1, data.begin() + b);
  size = data.size();
  std::cout << size << std::endl << data[0];
  for(int i = 1; i < size; ++i) std::cout << " " << data[i];
  std::cout << std::endl;
  return 0;
}
