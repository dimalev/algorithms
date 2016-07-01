#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Cut {
public:
  Cut(long min, long max, long count): min{min}, max{max}, count{count} { }

  long min;
  long max;
  long count;
};

std::ostream& operator<<(std::ostream& cout, const Cut& cut) {
  cout << "[" << cut.min << "-" << cut.max << ":" << cut.count << "]";
  return cout;
}

std::vector<Cut*> extend(const std::vector<Cut*> &input, long max) {
  std::vector<Cut*> res{};
  long min = std::numeric_limits<long>::max();

  Cut* last = input[input.size() - 1];
  Cut* final = nullptr;
  if(max > last->max)
    final = new Cut(0, max - last->max - 1, last->count + 2);

  for(Cut* cut : input) {
    if(cut->min > max) {
      delete cut;
      continue;
    }
    if(cut->max >= max) {
      cut->max = max - cut->min;
      cut->min = 0;
      cut->count += 1;
    } else {
      long mm = cut->max;
      cut->max = max - cut->min;
      cut->min = max - mm;
      cut->count += 1;
    }

    if(cut->count - 1 > min) {
      cut->count = min + 1;
    } else if(cut->count < min) min = cut->count;

    res.push_back(cut);
  }

  if(final != nullptr) {
    if(final->count - 1 > min) final->count = min + 1;
    res.push_back(final);
  }

  std::reverse(res.begin(), res.end());
  return res;
}

void dump(const std::vector<Cut*> &vec) {
  for(Cut* cut : vec) {
    std::cout << (*cut) << ", ";
  }
  std::cout << std::endl;
}

int main() {
  long n, m, first;
  std::cin >> n >> m;
  std::vector<long> Ns;
  while(n--) {
    long v;
    std::cin >> v;
    Ns.push_back(v);
  }

  std::sort(Ns.begin(), Ns.end());
  first = Ns[0] - 1;

  for(long i = 0; i < Ns.size() - 1; ++i) {
    Ns[i] = Ns[i + 1] - Ns[i] - 1;
  }
  Ns[Ns.size() - 1] = m - Ns[Ns.size() - 1];

  // for(long i : Ns) std::cout << i << std::endl;

  // std::cout << "---------------------" << std::endl;

  std::vector<Cut*> cuts;
  if(first != 0)
    cuts.push_back(new Cut(0, first - 1, 1));
  cuts.push_back(new Cut(first, first, 0));
  // dump(cuts);

  for(long l : Ns) {
    cuts = extend(cuts, l);
    // dump(cuts);
  }

  long mx = cuts[0]->count - 1;
  for(long i = 1; i < cuts.size(); ++i)
    if(cuts[i]->count < mx) mx = cuts[i]->count;

  std::cout << mx;

  return 0;
}
