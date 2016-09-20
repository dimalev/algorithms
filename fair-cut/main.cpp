#include <iostream>
#include <iterator>
#include <algorithm>

long take(int i, int j, int N, int K) {
  return 2 * (i - j) - N + K;
}

long drop(int i, int j, int N, int K) {
  return 2 * j - K;
}

int main() {
  int N, K;
  std::cin >> N >> K;
  long A[N];
  for(int i = 0; i < N; ++i) std::cin >> A[i];
  std::sort(A, A + N, std::less<long>());
#ifdef ALGO_DEBUG
  std::copy(A, A + N, std::ostream_iterator<long>(std::cerr, " "));
  std::cerr << std::endl;
  std::cerr << std::endl;
#endif
  long line[N];
  line[0] = drop(0, 0, N, K) * A[0];
  for(int i = 1; i < N; ++i) {
    line[i] = line[i - 1] + drop(i, 0, N, K) * A[i];
  }
#ifdef ALGO_DEBUG
  std::cerr << "0: ";
  std::copy(line, line + N, std::ostream_iterator<long>(std::cerr, " "));
  std::cerr << std::endl;
#endif
  for(int j = 1; j <= K; ++j) {
    long last;
    if(j == 1) {
      last = line[0];
      line[0] = take(0, 0, N, K) * A[0];
    } else {
      last = line[j - 1];
      line[j - 1] = line[j - 2] + take(j - 1, j - 1, N, K) * A[j - 1];
    }
    for(int i = std::max(1, j); i < N - (K - j); ++i) {
      long taken = last + take(i, j - 1, N, K) * A[i];
      long dropped = line[i - 1] + drop(i, j, N, K) * A[i];
      last = line[i];
      line[i] = std::min(taken, dropped);
    }
#ifdef ALGO_DEBUG
    std::cerr << j << ": ";
    std::copy(line, line + N, std::ostream_iterator<long>(std::cerr, " "));
    std::cerr << std::endl;
#endif
  }
  std::cout << line[N - 1] << std::endl;
  return 0;
}
