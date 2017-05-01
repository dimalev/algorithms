#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  std::map<std::string, int> cities;
  std::string room_names[16][100];
  std::set<int> rooms[24][16];
  int C;
  std::cin >> C;
  for(int c = 0; c < C; ++c) {
    std::string city_name;
    int room_count;
    std::cin >> city_name >> room_count;
    cities[city_name] = c;
    for(int n = 0; n < room_count; ++n) {
      std::string schedule, room_name;
      std::cin >> schedule >> room_name;
      room_names[c][n] = room_name;
      std::string noopy;
      std::getline(std::cin, noopy);
      room_names[c][n] = room_name;
      for(int i = 0; i < 24; ++i) {
        if(schedule[i] == '.') {
          rooms[i][c].insert(n);
        }
      }
    }
  }
  int Q;
  std::cin >> Q;
  for(int q = 0; q < Q; ++q) {
    int N;
    std::cin >> N;
    std::vector<int> cities_to_search;
    for(int n = 0; n < N; ++n) {
      std::string city_name;
      std::cin >> city_name;
      cities_to_search.push_back(cities[city_name]);
    }
    bool found = false;
    for(int t = 0; t < 24; ++t) {
      std::vector<int> rooms_found;
      bool is_good = true;
      for(int n = 0; n < N; ++n) {
        if(rooms[t][cities_to_search[n]].size() == 0) {
          is_good = false;
          break;
        }
        rooms_found.push_back(*rooms[t][cities_to_search[n]].begin());
      }
      if(is_good) {
        std::cout << "Yes";
        for(int n = 0; n < N; ++n) {
          std::cout << " " << room_names[cities_to_search[n]][rooms_found[n]];
        }
        std::cout << "\n";
        found = true;
        break;
      }
    }
    if(!found) {
      std::cout << "No\n";
    }
  }
  return 0;
}
