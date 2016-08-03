#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int bitsize = 61;

constexpr unsigned long long size = (1 << 31);

int main() {
  unsigned long long N, S, P, Q, a, i, diff = 1;
  cin >> N >> S >> P >> Q;
  vector<long> histo{};
  histo.resize(69273667);
  a = S % size;
  histo[a / bitsize] = (1 << (a % bitsize));
  for(i = 1; i < N; ++i) {
    a = (((a * P) % size) + Q) % size;
    // cout << a << " " << histo[a / 60] << endl;
    if((histo[a / bitsize] >> (a % bitsize)) % 2 == 0) {
      histo[a / bitsize] = (histo[a / bitsize] | (1 << (a % bitsize)));
      ++diff;
    } else break;
  }
  cout << diff << endl;
  return 0;
}
