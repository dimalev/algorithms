#include <iostream>
#include <cstdio>
#include <cmath>
#include <array>

const int N_MAX = 500;

int N, last_used = 1.0;

std::array<std::array<double, N_MAX>, N_MAX + 1> W;
std::array<double, N_MAX + 1> p;

void minus(int top, int bottom, double coef) {
  for(int i = 0; i < N; ++i) {
    W[bottom][i] -= W[top][i] * coef;
  }
  p[bottom] -= p[top] * coef;
}

double solve() {
  for(int z = 0; z < N - 1; ++z) {
    W[z + 1][z] -= 1.0f;
  }

#ifdef ALGO_DEBUG
  for(int z = 0; z < N + 1; ++z) {
    for(int j = 0; j < N; ++j) {
      fprintf(stderr, "%+.2f ", W[z][j]);
    }
    fprintf(stderr, "= %+.2f\n", p[z]);
  }

  fprintf(stderr, "\n");
#endif

  int k = 0, i = 0;
  for(; i <= N && k < N; ++i, ++k) {
    while(i <= N && std::abs(W[i][k]) < 0.0000001d) ++i;

    if(i > N) return -1.0d;

    for(int j = i + 1; j < N + 1; ++j) {
      if(W[j][k] != 0.0f)
        minus(i, j, W[j][k] / W[i][k]);
    }

#ifdef ALGO_DEBUG
    for(int z = 0; z < N + 1; ++z) {
      for(int j = 0; j < N; ++j) {
        fprintf(stderr, "%+.2f ", W[z][j]);
      }
      fprintf(stderr, "= %+.2f\n", p[z]);
    }

    fprintf(stderr, "\n");
#endif
  }

  --k;
  while(i >= 0) {
    if(std::abs(W[i][k]) < 0.000001) --i;
    else {
      p[i] = p[i] / W[i][k];
      for(int j = 0; j < i; ++j) {
        if(W[j][i] != 0.0f)
          minus(i, j, W[j][i]);
      }
      --k;
    }
  }

#ifdef ALGO_DEBUG
  for(int z = 0; z < N + 1; ++z) {
    for(int j = 0; j < N; ++j) {
      fprintf(stderr, "%+.2f ", W[z][j]);
    }
    fprintf(stderr, "= %+.2f\n", p[z]);
  }

  fprintf(stderr, "\n");
#endif

  return p[0];
}

int main() {
  std::cin >> N;
  p[0] = 1.0d;
  for(int i = 0; i < N; ++i) {
    W[0][i] = 1.0d;
    p[i + 1] = 0.0d;
    for(int j = 0; j < N; ++j) {
      std::cin >> W[j + 1][i];
    }
  }

  printf("%.10f\n", solve());
  return 0;
}
