#include <iostream>
#include <vector>
#include <set>

class Kill {
public:
  Kill(long minM, long monsterId, long gain): minM{minM}, monsterId{monsterId}, gain{gain} {}

  long minM;
  long monsterId;
  long gain;
};

Kill* findMaxMonster(std::vector<Kill> &kills, long M) {
  for(Kill& killer : kills) {
    if(killer.minM >= M) return &killer;
  }
  return nullptr;
}

int main() {
  std::vector<Kill> maxMonster;
  long n, M,
    minM = -1L, // minimum M required to reach so far
    accB = 0L, // accumulation per straight wins
    fights = 0L; // fights required so far
  std::cin >> n >> M;
  for(long i = 0L; i < n; ++i) {
    long a, b, c;
    std::cin >> a >> b >> c;
    long newMinM = a - accB;
    if(newMinM > minM) {
      minM = newMinM;
      maxMonster.push_back(Kill(minM, i, accB - c));
    }
    accB += b;
  }
  std::set<long> Ms;
  long i = 0L;
  long pM = -1L;
  long Msize = maxMonster.size();
  while(M >= 0) {
    while(true) {
      if(M > pM) {
        if(i >= Msize) {
          std::cout << fights + n;
          return 0;
        }
        if(maxMonster[i].minM >= M) break;
        ++i;
      } else {
        if(i == 0) {
          std::cout << -1;
          return 0;
        }
        if(maxMonster[i - 1].minM < M) break;
        --i;
      }
    }
    pM = M;
    fights += maxMonster[i].monsterId + 1;
    M += maxMonster[i].gain;
    if(maxMonster[i].gain == 0) {
      std::cout << -1;
      return 0;
    }
    // std::cout << maxMonster[i].minM << " "
    //           << maxMonster[i].monsterId << " "
    //           << maxMonster[i].gain << " => "
    //           << M << std::endl;
    if(Ms.find(M) != Ms.end()) {
      std::cout << -1;
      return 0;
    }
    Ms.insert(M);
  }
  std::cout << -1;
}
