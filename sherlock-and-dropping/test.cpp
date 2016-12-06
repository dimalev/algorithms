#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

class sample {
public:
  sample(int y) : y(y) {}
  int y;

  bool operator<(const sample &other) const { return y < other.y; }
};

std::ostream& operator<<(std::ostream &out, const sample *out_sample) {
  out << out_sample->y;
  return out;
}

class sample_pointer_less {
public:
  sample_pointer_less() { std::cout << "sample pointer is built\n"; }
  bool operator()(const sample *left, const sample *right) {
    return *left < *right;
  }
};

int main() {
  std::set<sample*, sample_pointer_less> s;
  s.insert(new sample(12));
  s.insert(new sample(59));
  s.insert(new sample(3));
  s.insert(new sample(9));
  s.insert(new sample(45));
  s.insert(new sample(28));
  std::copy(s.begin(), s.end(), std::ostream_iterator<sample*>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
