#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cmath>

const float pi = 3.14159265359;
const float r = 6371;

class Destination {
public:
  explicit Destination() {}
  explicit Destination(std::string name, float ln, float lt): name{name},ln{ln}, lt{lt} {}
  explicit Destination(const Destination& dst): name{dst.name},ln{dst.ln}, lt{dst.lt}, interests{dst.interests} {}
  virtual ~Destination() {}

  float ln, lt;
  std::set<std::string> interests;
  std::string name;
};

float d2r(float d) {
  return d * pi / 180;
}

float dest(const Destination& d1, const Destination& d2) {
  float d1_lat_rad = d2r(d1.lt);
  float d2_lat_rad = d2r(d2.lt);
  float d1_long_rad = d2r(d1.ln);
  float d2_long_rad = d2r(d2.ln);

  return std::acos( std::sin(d1_lat_rad) * std::sin(d2_lat_rad) +
                    std::cos(d1_lat_rad) * std::cos(d2_lat_rad) *
                    std::cos(d1_long_rad - d2_long_rad) ) * r;
}

int main() {
  int n, m;
  std::cin >> n;
  std::set<std::string> interests;
  for(int i = 0; i < n; ++i) {
    int q;
    std::cin >> q;
    for(int j = 0; j < q;++j) {
      std::string interest;
      std::cin >> interest;
      interests.insert(interest);
    }
  }
  #ifdef ALGO_DEBUG
  std::cerr << "Interests read" << std::endl;
  #endif

  std::cin >> m;
  Destination destinations[m];
  for(int i = 0; i < m; ++i) {
    #ifdef ALGO_DEBUG
    std::cerr << "reading " << i << " destination" << std::endl;
    #endif
    std::string dest_name;
    float ln, lt;
    std::cin >> destinations[i].name >> destinations[i].lt >> destinations[i].ln;
    int q;
    std::cin >> q;
    for(int j = 0; j < q; ++j) {
      std::string interest;
      std::cin >> interest;
      auto iit = interests.find(interest);
      if(iit != interests.end()) {
        destinations[i].interests.insert(interest);
      }
    }
  }
  int max_interests = 0;
  Destination out1, out2;
  for(int i = 0; i < m - 1; ++i) {
    Destination& dst1 = destinations[i];
    for(int j = i + 1; j < m; ++j) {
      Destination& dst2 = destinations[j];
  #ifdef ALGO_DEBUG
      std::cerr << dst1.name << " - " << dst2.name << ": " << dest(dst1, dst2) << std::endl;
  #endif
      if(dst1.name == dst2.name) continue;
      std::set<std::string> common{dst1.interests};
      common.insert(dst2.interests.begin(), dst2.interests.end());
      if(common.size() > max_interests) {
        max_interests = common.size();
        out1 = dst1;
        out2 = dst2;
      } else if(common.size() == max_interests) {
        if(dest(out1, out2) > dest(dst1, dst2)) {
          out1 = dst1;
          out2 = dst2;
        }
      }
    }
  }
  if(out1.name > out2.name) std::cout << out2.name << " " << out1.name << std::endl;
  else std::cout << out1.name << " " << out2.name << std::endl;
  return 0;
}
