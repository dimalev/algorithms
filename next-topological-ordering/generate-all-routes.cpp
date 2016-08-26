#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

const int N_MAX = 100000;

int N, M;
std::set<int> links[N_MAX];
int arity[N_MAX];

bool used[N_MAX];

std::vector<int*> permutations;
int current_permutation[N_MAX];

void push_vertice(int id, int left) {
  current_permutation[N - left - 1] = id;
  if(left == 0) {
    int *copy = (int*)malloc(sizeof(int) * N);
    std::memcpy(copy, current_permutation, sizeof(int) * N);
    permutations.push_back(copy);
    return;
  }
  used[id] = true;
  for(int v : links[id]) arity[v]--;
  for(int i = 0; i < N; ++i) {
    if(arity[i] == 0 && !used[i])
      push_vertice(i, left - 1);
  }
  used[id] = false;
  for(int v : links[id]) arity[v]++;
}

int main() {
  std::cin >> N >> M;
  std::memset(arity, 0, sizeof(int) * N);
  for(int i = 0; i < M; ++i) {
    int u, v;
    std::cin >> u >> v;
    links[u - 1].insert(v - 1);
    ++arity[v - 1];
  }
  std::memset(used, false, sizeof(bool) * N);
  for(int i = 0; i < N; ++i) {
    if(arity[i] == 0) push_vertice(i, N - 1);
  }
  int sz = permutations.size();
  char filename[100];
  for(int i = 0; i < sz - 1; ++i) {
    int *current = permutations[i], *nextp = permutations[i + 1];
    sprintf(filename, "input-%d.txt", i + 10);
    std::ofstream input;
    input.open(filename);
    input << N << " " << M << std::endl;
    for(int j = 0; j < N; ++j)
      for(int k : links[j])
        input << (j + 1) << " " << (k + 1) << std::endl;
    input << (current[0] + 1);
    for(int j = 1; j < N; ++j) input << " " << (current[j] + 1);
    input << std::endl;
    input.close();
    sprintf(filename, "output-%d.txt", i + 10);
    std::ofstream output;
    output.open(filename);
    output << (nextp[0] + 1);
    for(int j = 1; j < N; ++j) output << " " << (nextp[j] + 1);
    output << std::endl;
    output.close();
  }
  return 0;
}
