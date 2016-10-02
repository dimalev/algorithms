#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

const unsigned long start = 1465948800;
const unsigned long end = 1468540799;

class Reviewer {
public:
  int id;
  std::map<std::string, int> interests;
};

int main() {
  int n, m;
  char c;
  std::cin >> n >> m;
  std::cin.get();
  std::vector<std::string> interests;
  for(int i = 0; i < n; ++i) {
    std::string interest;
    std::getline(std::cin, interest, '\n');
    std::transform(interest.begin(), interest.end(), interest.begin(), ::tolower);
    TRACE_LINE("i[" << i << "]: " << interest);
    interests.push_back(interest);
  }
  std::map<int, Reviewer*> reviewers;
  for(int i = 0; i < m; ++i) {
    int r;
    unsigned long t;
    std::cin >> r >> t;
    std::string body;
    std::getline(std::cin, body, '\n');
    std::getline(std::cin, body, '\n');
    std::transform(body.begin(), body.end(), body.begin(), ::tolower);
    TRACE_LINE(body << std::endl);
    auto rit = reviewers.find(r);
    Reviewer* reviewer = nullptr;
    if(rit != reviewers.end()) {
      reviewer = rit->second;
    } else {
      reviewer = new Reviewer{};
      reviewer->id = r;
      for(std::string interest : interests) {
        reviewer->interests[interest] = 0;
      }
      reviewers[r] = reviewer;
    }
    for(std::string interest : interests) {
      auto tit = body.find(interest);
      if(tit != std::string::npos) {
        int score = 0;
        if(t < start || t > end) score += 10;
        else score += 20;
        if(body.length() < 100) score += 10;
        else score += 20;
        reviewer->interests[interest] += score;
      }
    }
  }
  for(std::string interest : interests) {
    Reviewer *r = nullptr;
    int score = 0;
    for(auto rp : reviewers) {
      Reviewer* cr = rp.second;
      if(cr->interests[interest] > score) {
        score = cr->interests[interest];
        r = cr;
      } else if(score > 0 && cr->interests[interest] == score && cr->id < r->id) {
        r = cr;
      }
    }
    if(r != nullptr) std::cout << r->id << std::endl;
    else std::cout << -1 << std::endl;
  }
  return 0;
}
