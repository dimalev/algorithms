#include <iostream>
#include <array>

template<int S>
class Mapping {
public:
  static constexpr int max_code = 1 << S;
  int get_value(int comb) const {
    int max = ((S << 1) - 1);
    int sub = comb & max;
    if(sub < S) return sub;
    return max - sub;
  }
  bool has_value(int from, int point) const {
    int twist = max_code;
    do {
      twist = twist >> 1;
      int new_value = from ^ twist;
      if(get_value(new_value) == point) return true;
    } while(twist > 0);
    return false;
  }
};

constexpr int count = 4;

int main() {
  Mapping<count> map;
  for(int i = 0; i < Mapping<count>::max_code; ++i) {
    for(int j = 0; j < count; ++j) {
      if(!map.has_value(i, j)) std::cout << "cannot reach " << j << " from " << i << std::endl;
    }
  }
  return 0;
}
