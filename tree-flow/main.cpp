#include <iostream>
#include <algorithm>

class edge {
public:
  edge() {}
  explicit edge(long start, long end, long length) : start{start}, end{end}, length{length} {}
  void sort() {
    if(end < start) std::swap(end, start);
  }
  ~edge() {}
  long start, end, length;

  bool operator<(const edge &right) {
    return this->start < right.start || (!(right.start < this->start) && this->end < right.end);
  }
};

std::istream& operator>>(std::istream &in, edge &res) {
  in >> res.start >> res.end >> res.length;
  res.sort();
  return in;
}

std::ostream& operator<<(std::ostream &out, const edge &line) {
  out << line.start << " " << line.end << " " << line.length;
  return out;
}

// we will count distance from point `from` to all the points available in `all`
void distances(long from, edge * const all, long total, long *res) {
  long a, b;
  edge *lala = std::lower_bound(all, all + total, nullptr, [&from](const edge &item, const edge &_) { item.start < from; });
  std::cout << a << " " << b << std::endl;
}

int main() {
  long N, res = 0;
  std::cin >> N;
  edge all[N - 1];
  for(int i = 0; i < N - 1; ++i) {
    std::cin >> all[i];
    res += all[i].length;
  }
  std::sort(all, all + (N - 1));
  for(const edge &line : all) {
    std::cout << line << std::endl;
  }
  std::cout << res << std::endl;
  return 0;
}
