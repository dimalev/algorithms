#include <iostream>
#include <vector>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

constexpr int MAX_N = 5000;
constexpr int MAX_K = 5000;

int N, K;
std::vector<long long> W;
std::vector<long long> X;

long long** min_fare = new long long*[MAX_K];
std::vector<bool> is_fare_computed(MAX_K);

inline long long& at(long long *mass, int x, int y) {
  return mass[x * N + y];
}

long long compute_min_fare_cell(int start, int end, int left_piles, int right_piles) {
  long long left_cost = at(min_fare[left_piles], start, start + left_piles - 1);
  long long right_cost = at(min_fare[right_piles], start + left_piles, end);
  long long min_value = left_cost + right_cost;
  for(int middle = start + left_piles; middle < end - right_piles + 2; ++middle) {
    long long left_cost = at(min_fare[left_piles], start, middle - 1);
    long long right_cost = at(min_fare[right_piles], middle, end);
    // print("test for {} L={} R={}".format(middle, left_cost, right_cost))
    min_value = std::min(min_value, left_cost + right_cost);
  }
  return min_value;
}

void compute_min_fare(int piles) {
  min_fare[piles] = new long long[N * N];
  is_fare_computed[piles] = true;
  if(piles == 1) {
    std::cout << "computing fare for " << piles << std::endl;
    for(int start = 0; start < N; ++start) {
      long long total_w = W[start];
      for(int end = start + 1; end < N; ++end) {
        at(min_fare[1], start, end) += at(min_fare[1], start, end - 1) + total_w * (X[end - 1] - X[end]);
        total_w += W[end];
      }
    }
    // for(int i = 0; i < N * N; ++i) {
    //   std::cout << min_fare[1][i];
    //   if(i % N == N - 1)
    //     std::cout << "\n";
    //   else
    //     std::cout << "\t";
    // }
    return;
  }
  int left_piles = piles / 2;
  int right_piles = piles - left_piles;
  if(!is_fare_computed[left_piles])
    compute_min_fare(left_piles);
  if(!is_fare_computed[right_piles])
    compute_min_fare(right_piles);
  std::cout << "computing fare for " << piles << std::endl;

  for(int start = 0; start < N - piles + 1; ++start) {
    std::cout << "at " << start << std::endl;
    for(int end = start + piles - 1; end < N; ++end) {
      at(min_fare[piles], start, end) = compute_min_fare_cell(start, end, left_piles, right_piles);
    }
  }
}

void unit_tests() {
}

int main() {
  // UNIT_TESTS();
  std::cin >> N >> K;
  if(K == 1) {
    long long result = 0, total_w, last_x;
    std::cin >> last_x >> total_w;
    for(int i = 1; i < N; ++i) {
      long long x, w;
      std::cin >> x >> w;
      result += total_w * (x - last_x);
      total_w += w;
      last_x = x;
    }
    std::cout << result << std::endl;
    return 0;
  }
  W.resize(N);
  X.resize(N);
  for(int i = 0; i < N; ++i) {
    long long x, w;
    std::cin >> x >> w;
    W.push_back(w);
    X.push_back(x);
  }
  std::reverse(W.begin(), W.end());
  std::reverse(X.begin(), X.end());
  int K_left = K / 2;
  int K_right = K - K_left;
  compute_min_fare(K_left);
  if(!is_fare_computed[K_right]) {
    compute_min_fare(K_right);
  }
  std::cout << compute_min_fare_cell(0, N - 1, K_left, K_right) << std::endl;
  return 0;
}
