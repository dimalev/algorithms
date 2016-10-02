#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

int main() {
  int T;
  std::cin >> T;
  int visited[1000], verticeid[1000], verticenext[1000], visitMatrix[1000][1001];
  for(int i = 0; i < T; ++i) {
    int n;
    std::cin >> n;
    std::vector<std::string> places;
    std::memset(&visitMatrix, 0, 1000 * 1001 * sizeof(int));
    std::string noop;
    std::getline(std::cin, noop);
    for(int j = 0; j < n; ++j) {
      std::string line;
      std::getline(std::cin, line);
      std::size_t comma = 0;
      std::size_t next_comma = line.find(',');
      int currp, prevp = -1;
      std::string place;
      while(next_comma < line.size() && next_comma != std::string::npos) {
        place = line.substr(comma, next_comma - comma);
        for(currp = 0; currp < places.size() && places[currp] != place; ++currp);
        TRACE_LINE("[" << place << "] " << prevp << " -> " << currp);
        if(currp == places.size()) places.push_back(place);
        if(prevp != -1) {
          visitMatrix[prevp][++visitMatrix[prevp][0]] = currp;
        }
        prevp = currp;
        comma = next_comma + 1;
        next_comma = line.find(",", comma);
      }
      place = line.substr(comma);
      if(place != "") {
        for(currp = 0; currp < places.size() && places[currp] != place; ++currp);
        TRACE_LINE("[" << place << "] " << prevp << " -> " << currp);
        if(currp == places.size()) places.push_back(place);
        if(prevp != -1) {
          visitMatrix[prevp][++visitMatrix[prevp][0]] = currp;
        }
      }
    }
    int count = places.size();
    std::memset(&verticenext, 0, 1000 * sizeof(int));
    std::memset(&verticeid, 0, 1000 * sizeof(int));
    std::memset(&visited, 0, 1000 * sizeof(int));
    bool violated = false;
    for(int j = 0; j < count; ++j) {
      if(visited[j] != 0) continue;
      verticenext[0] = 0;
      verticeid[0] = j;
      int k = 0;
      TRACE_LINE("start from: " << j);
      while(k >= 0) {
        int interest = verticeid[k];
        if(verticenext[k] >= visitMatrix[interest][0]) {
          TRACE_LINE("leaving: " << interest);
          visited[interest] = -1;
          --k;
        } else {
          int next = visitMatrix[interest][++verticenext[k]];
          if(visited[next] == j + 1) {
            TRACE_LINE("visiting: " << next << " again!");
            std::cout << "ORDER VIOLATION" << std::endl;
            violated = true;
            break;
          } else if(visited[next] == 0) {
            TRACE_LINE("visiting: " << next);
            visited[next] = j + 1;
            ++k;
            verticenext[k] = 0;
            verticeid[k] = next;
          }
        }
        if(violated) break;
      }
      if(violated) break;
    }
    if(violated) continue;
    std::cout << "ORDER EXISTS" << std::endl;
  }
}
