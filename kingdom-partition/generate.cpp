#include <iostream>
#include <random>
#include <set>

class point {
 public:
  int x, y;
  point(int x, int y) : x{x}, y{y} {
  }

  bool operator==(const point& other) {
    return x == other.x && y == other.y;
  }
};

bool operator<(const point& one, const point& two) {
  if(one.x == two.x) return one.y < two.y;
  return one.x < two.x;
}

int main() {
  int R = 50, C = 50, K = 12;
  std::set<point> P;
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, 49);
  while(P.size() < 2 * K) {
    int x = distribution(generator);
    int y = distribution(generator);
    P.insert({x, y});
  }
  std::cout << R << " " << C << " " << K << std::endl;
  int c = 0;
  for(point p : P) {
    std::cout << p.x << " " << p.y << std::endl;
  }
}
