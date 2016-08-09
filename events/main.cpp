#include <iostream>
#include <cstring>

int p2e_count[100];
int p2e[100][100];
int n;
int owners[100];

bool canTake(int p, int e) {
  if(owners[e] == 0) {
    return true;
  }
  int other = owners[e] - 1;
  for(int i = p2e_count[other] - 2; i >= 0; --i) {
    if(canTake(i, p2e[other][i])) return true;
  }
  return false;
}

void take(int p, int e) {
  if(owners[e] == 0) {
    owners[e] = p + 1;
    return;
  }
  int other = owners[e] - 1;
  owners[e] = p + 1;
  --p2e_count[other];
  while(p2e_count[other] > 0) {
    if(canTake(other, p2e[other][p2e_count[other] - 1])) {
      take(other, p2e[other][p2e_count[other] - 1]);
      return;
    }
    --p2e_count[other];
  }
}

int main() {
  std::cin >> n;
  std::string passions[1000];
  int posessors_count[1000];
  int posessors[1000][100];
  int passion_count = 0;
  for(int i = 0; i < n; ++i) {
    int _t, m;
    std::cin >> _t >> m;
    std::string passion;
    for(int j = 0; j < m; ++j) {
      std::cin >> passion;
      int k;
      for(k = 0; k < passion_count && passions[k] != passion; ++k);
      if(k == passion_count) {
        passions[passion_count] = passion;
        posessors_count[passion_count] = 0;
        ++passion_count;
      }
      posessors[k][posessors_count[k]++] = i;
    }
  }
  std::memset(&p2e_count, 0, 100 * sizeof(int));
  for(int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;
    for(int j =  0; j < m; ++j) {
      std::string passion;
      std::cin >> passion;
      int k;
      for(k = 0; k < passion_count && passions[k] != passion; ++k);
      if(k == passion_count) continue;
      for(int p = 0; p < posessors_count[k]; ++p) {
        int posessor = posessors[k][p];
        if(p2e_count[posessor] == 0 || p2e[posessor][p2e_count[posessor] - 1] < i) {
          p2e[posessor][p2e_count[posessor]] = i;
          ++p2e_count[posessor];
        }
      }
    }
  }
  std::memset(&owners, 0, 100 * sizeof(int));
  int total = 0;
  for(int i = 0; i < n; ++i) {
    while(p2e_count[i] > 0) {
      if(canTake(i, p2e[i][p2e_count[i] - 1])) {
        take(i, p2e[i][p2e_count[i] - 1]);
        ++total;
        break;
      }
      --p2e_count[i];
    }
  }
  std::cout << total << std::endl;
}
