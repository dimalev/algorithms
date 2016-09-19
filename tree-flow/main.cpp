#include <iostream>

class edge {
public:
  edge() {}
  explicit edge(long start, long end, long length) : start{start}, end{end}, length{length} {}
  ~edge() {}
  long start, end, length;
};

std::istream& operator>>(std::istream &in, edge &res) {
  in >> res.start >> res.end >> res.length;
  return in;
}

int main() {
  long N, res = 0;
  std::cin >> N;
  edge all[N - 1];
  for(int i = 0; i < N - 1; ++i) {
    std::cin >> all[i];
    res += all[i].length;
  }
  std::cout << res << std::endl;
  return 0;
}
