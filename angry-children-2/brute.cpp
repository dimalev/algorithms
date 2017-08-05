#include <iostream>
#include <vector>
#include <limits>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

std::vector<bool> best;
long long best_sum = std::numeric_limits<long long>::max();

long long find(std::vector<bool> &taken, std::vector<long long> &values,
               int left, long long score) {
  if(left == 0) {
    if(score < best_sum) {
      best_sum = score;
      best = taken;
    }
    return score;
  }
  int count = values.size();
  long long sum = std::numeric_limits<long long>::max();
  fr(i,0,count) {
    if(taken[i]) continue;
    long long new_sum = score;
    fr(j, 0,count) if(taken[j]) new_sum += std::abs(values[j] - values[i]);
    taken[i] = true;
    if(new_sum < sum) {
      new_sum = find(taken, values, left - 1, new_sum);
      if(new_sum < sum) {
        sum = new_sum;
      }
    }
    taken[i] = false;
  }
  return sum;
}

int main() {
  std::vector<long long> values;
  int N, K;
  std::cin >> N >> K;
  values.resize(N);
  fr(i,0,N) std::cin >> values[i];
  std::vector<bool> taken(N);
  std::cout << find(taken, values, K, 0ll) << std::endl;
  fr(i,0,N) if(best[i]) std::cout << values[i] << std::endl;
  return 0;
}
