#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

int V[21];
int path[21][21];
int n;
int max_total = 0;
int max_visit[21];
int visit[21];
bool visited[21];

void go(int city, int days, int hours, int depth) {
  if(V[city] < hours) {
    hours -= V[city];
  } else {
    int more = V[city] - hours;
    days -= 1 + more / 16;
    hours = 16 - (more % 16);
  }
  if(days < 0 || (days == 0 && hours < 16)) return;
  visit[depth] = city;
  visited[city] = true;
  if(depth > max_total) {
    max_total = depth;
    for(int i = 1; i <= max_total; ++i) max_visit[i] = visit[i];
  }
  for(int i = 1; i <= n; ++i) {
    if(visited[i] || path[city][i] == 0) continue;
    int d = path[city][i];
    if(hours > d) {
      go(i, days, hours - d, depth + 1);
    } else if(hours == d) {
      go(i, days - 1, 16, depth + 1);
    } else if(hours < d) {
      if(d < 16) go(i, days - 1, 16 - d, depth + 1);
      else if(d == 16) go(i, days - 2, 16, depth + 1);
    }
  }
  visited[city] = false;
}

int main() {
  std::cin >> n;
  std::string cities[21];
  cities[0] = "Bevagna";
  V[0] = 0;
  std::string line;
  std::getline(std::cin, line);
  for(int i = 1; i <= n; ++i) {
    std::getline(std::cin, line);
    size_t comma = line.find(',');
    cities[i] = line.substr(0, comma);
    V[i] = std::atoi(line.substr(comma + 1).c_str());
  }
  int m;
  std::cin >> m;
  std::getline(std::cin, line);
  std::memset(&path, 0, 21 * 21 * sizeof(int));
  for(int i = 0; i < m; ++i) {
    std::getline(std::cin, line);
    size_t comma1 = line.find(','), comma2 = line.find(',', comma1 + 1);
    std::string from = line.substr(0, comma1);
    std::string to = line.substr(comma1 + 1, comma2 - comma1 - 1);
    int d = std::atoi(line.substr(comma2 + 1).c_str());
    int a = 0, b = 0;
    while(cities[a] != from) ++a;
    while(cities[b] != to) ++b;
    path[a][b] = d;
    path[b][a] = d;
  }
  std::memset(&visited, false, 21*sizeof(bool));
  go(0, 6, 16, 0);
  if(max_total < 1) {
    std::cout << "NONE" << std::endl;
    return 0;
  }
  for(int i = 1; i <= max_total; ++i) {
    std::cout << cities[max_visit[i]] << std::endl;
  }
  return 0;
}
