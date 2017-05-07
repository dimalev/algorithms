#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

int sMax = 0;

int score(int s, int p) {
  return (160000 * s) / (p * p);
}

class map {
  int rows, cols;
  int *owners;
  int next_owner;
  int S[16], P[16];
 public:
  map(int rows, int cols) : rows{rows}, cols{cols}, next_owner{1},
                            owners{new int[rows * cols]}
  {
    std::fill_n(owners, rows * cols, 0);
  }

  map(const map &other) : rows{other.rows}, cols{other.cols},
                          next_owner{other.next_owner},
                          owners{new int[other.rows * other.cols]}
  {
    for(int r = 0; r < rows; ++r) {
      for(int c = 0; c < cols; ++c) {
        owners[r * cols + c] = other.owners[r * cols + c];
      }
    }
    for(int i = 0; i < 16; ++i) {
      S[i] = other.S[i];
      P[i] = other.P[i];
    }
  }

  ~map() {
    delete[] owners;
  }

  int get_next_owner() {
    S[next_owner] = 0;
    P[next_owner] = 0;
    return next_owner++;
  }

  int get_score(int owner) {
    return score(S[owner], P[owner]);
  }

  int get_S(int owner) {
    return S[owner];
  }

  int get_P(int owner) {
    return P[owner];
  }

  int get_total_score() {
    int total = 0;
    for(int i = 1; i < next_owner; ++i) {
      total += get_score(i);
    }
    return total / (next_owner - 1);
  }

  int dP(int r, int c, int owner) {
    int dP = 4;
    if(r > 0 && owners[(r - 1) * cols + c] == owner) dP -= 2;
    if(r < rows - 1 && owners[(r + 1) * cols + c] == owner) dP -= 2;
    if(c > 0 && owners[r * cols + c - 1] == owner) dP -= 2;
    if(c < cols - 1 && owners[r * cols + c + 1] == owner) dP -= 2;
    return dP;
  }

  int get_owner(int r, int c) {
    return owners[r * cols + c];
  }

  void set_owner(int r, int c, int owner) {
    if(owners[r * cols + c] == owner) return;
    owners[r * cols + c] = owner;
    S[owner]++;
    P[owner] += dP(r, c, owner);
  }

  std::vector<std::pair<int, int>> path(int r0, int c0, int r1, int c1) const {
    for(int s = sMax; s >= 0; --s) {
      int temp[rows][cols];
      for(int r = 0; r < rows; ++r)
        for(int c = 0; c < cols; ++c) {
          if((r == r0 && c == c0) || (r == r1 && c == c1)) {
            temp[r][c] = 0;
          } else if(owners[r * cols + c] != 0)
            temp[r][c] = -1;
          else {
            if((abs(r - r0) <= s && abs(c - c0) <= s) ||
               (abs(r - r1) <= s && abs(c - c1) <= s)) {
              temp[r][c] = 0;
            } else {
              if(r < s || c < s || r >= rows - s || c >= cols - s) {
                temp[r][c] = -1;
              } else {
                bool isBlocked = false;
                for(int dr = -s; dr <= s; ++dr) {
                  for(int dc = -s; dc <= s; ++dc) {
                    if(r + dr >= 0 && c + dc >= 0 &&
                       r + dr < rows && c + dc < cols) {
                      if(owners[(r + dr) * cols + c + dc] != 0) {
                        isBlocked = true;
                        break;
                      }
                    }
                  }
                  if(isBlocked) break;
                }
                temp[r][c] = isBlocked ? -1 : 0;
              }
            }
          }
        }
      std::queue<std::pair<int, int>> line;
      line.emplace(r0, c0);
      temp[r0][c0] = 1;
      while(!line.empty()) {
        auto next_pair = line.front();
        line.pop();
        int r = next_pair.first;
        int c = next_pair.second;
        if(r == r1 && c == c1) {
          std::vector<std::pair<int, int>> res;
          while(temp[r][c] > 1) {
            res.push_back({r, c});
            if(r > 0 && temp[r][c] - 1 == temp[r - 1][c]) --r;
            else if(r < rows - 1 && temp[r][c] - 1 == temp[r + 1][c]) ++r;
            else if(c > 0 && temp[r][c] - 1 == temp[r][c - 1]) --c;
            else if(c < cols - 1 && temp[r][c] - 1 == temp[r][c + 1]) ++c;
          }
          res.push_back({r, c});
          return res;
        }
        if(r > 0 && temp[r - 1][c] == 0) {
          temp[r - 1][c] = temp[r][c] + 1;
          line.emplace(r - 1, c);
        }
        if(r < rows - 1 && temp[r + 1][c] == 0) {
          temp[r + 1][c] = temp[r][c] + 1;
          line.emplace(r + 1, c);
        }
        if(c > 0 && temp[r][c - 1] == 0) {
          temp[r][c - 1] = temp[r][c] + 1;
          line.emplace(r, c - 1);
        }
        if(c < cols - 1 && temp[r][c + 1] == 0) {
          temp[r][c + 1] = temp[r][c] + 1;
          line.emplace(r, c + 1);
        }
      }
    }
    return {};
  }

  void operator=(const map &other) {
    if(rows != other.rows || cols != other.cols) {
      delete[] owners;
      rows = other.rows;
      cols = other.cols;
      owners = new int[rows * cols];
    }
    next_owner = other.next_owner;
    std::copy_n(other.owners, rows * cols, owners);
    std::copy_n(other.S, 16, S);
    std::copy_n(other.P, 16, P);
  }

  std::string toDebugString() {
    char res[rows * (cols + 1) + 1];
    res[rows * (cols + 1)] = '\0';
    for(int r = 0; r < rows; ++r) {
      res[(r + 1) * (cols + 1) - 1] = '\n';
      for(int c = 0; c < cols; ++c)
        if(owners[r * cols + c] == 0) res[r * (cols + 1) + c] = '.';
        else res[r * (cols + 1) + c] = 'a' + owners[r * cols + c];
    }
    return res;
  }

  std::string statisticString() {
    std::stringstream statistics;
    statistics << toDebugString();
    for(int i = 1; i < next_owner; ++i) {
      statistics << char('a' + i) << ": S=" << S[i] << ", P=" << P[i]
                 << std::endl;
    }
    statistics << get_total_score() << std::endl;
    return statistics.str();
  }

  int fill(int r_start, int r_end, int dr,
           int c_start, int c_end, int dc) {
    bool capable = true;
    while(capable) {
      capable = false;
      for(int r = r_start; r != r_end; r += dr) {
        for(int c = c_start; c != c_end; c += dc) {
          if(get_owner(r, c) > 0) continue;
          std::set<int> vars;
          if(r > 0 && get_owner(r - 1, c) > 0)
            vars.insert(get_owner(r - 1, c));
          if(r < rows - 1 && get_owner(r + 1, c) > 0)
            vars.insert(get_owner(r + 1, c));
          if(c > 0 && get_owner(r, c - 1) > 0)
            vars.insert(get_owner(r, c - 1));
          if(c < cols - 1 && get_owner(r, c + 1) > 0)
            vars.insert(get_owner(r, c + 1));
          if(!vars.empty()) {
            int best_dp = 1e9;
            int best_S = 0;
            int best_v = 0;
            for(int var : vars) {
              int dp = dP(r, c, var);
              if(dp < best_dp) {
                best_dp = dp;
                best_S = S[var];
                best_v = var;
              } else if(dp == best_dp && S[var] < best_S) {
                best_dp = dp;
                best_S = S[var];
                best_v = var;
              }
            }
            set_owner(r, c, best_v);
            capable = true;
          }
        }
      }
    }
    return get_total_score();
  }
};

struct entity {
  enum type {
    life, mana
  };

  entity(): t{type::life}, x{0}, y{0} {}
  entity(type t, int x, int y): t{t}, x{x}, y{y} {}

  type t;
  int x, y;
};

using entity_pair = std::pair<entity, entity>;

bool operator==(const entity &one, const entity &two) {
  return one.t == two.t && one.x == two.x && one.y == two.y;
}
bool operator!=(const entity &one, const entity &two) {
  return !(one == two);
}

class radial_less {
  entity center;

  int level(int dx, int dy) {
    if(dx >= 0 && dy < 0) {
      return 1;
    }
    if(dx > 0 && dy >= 0) {
      return 2;
    }
    if(dx <= 0 && dy > 0) {
      return 3;
    }
    if(dx < 0 && dy <= 0) {
      return 4;
    }
  }
 public:
  radial_less(const entity &center): center{center} {}

  bool operator()(const entity &left, const entity &right) {
    if(right == center) return false;
    if(left == center) return true;
    int dx1 = left.x - center.x;
    int dy1 = left.y - center.y;
    int dx2 = right.x - center.x;
    int dy2 = right.y - center.y;
    int l1 = level(dx1, dy1);
    int l2 = level(dx2, dy2);
    if(l1 < l2) return true;
    if(l1 > l2) return false;
    if(dy1 * dx2 == dy2 * dx1) {
      if(dy1 != dy2)
        return std::abs(dy1) < std::abs(dy2);
      else
        return std::abs(dx1) < std::abs(dx2);
    }
    return dy2 * dx1 > dy1 * dx2;
  }
};

std::string toDebugString(const entity &e) {
  char buf[100];
  std::sprintf(buf, "%c(%d, %d)",
               e.t == entity::type::life ? 'L' : 'M', e.x, e.y);
  return buf;
}

std::vector<entity> convex_hull(const std::vector<entity> &E) {
  std::vector<entity> sorted{E};
  entity smallest = sorted[0];
  int l = E.size();
  for(int i = 1; i < l; ++i) {
    if((E[i].x < smallest.x) ||
           (E[i].x == smallest.x && E[i].y < smallest.y)) {
      smallest = E[i];
    }
  }
  std::sort(sorted.begin(), sorted.end(), radial_less{smallest});
  entity hull[l];
  hull[0] = sorted[0];
  hull[1] = sorted[1];
  int next = 2, hull_l = 2;
  while(next < l) {
    while(hull_l > 1) {
      radial_less comp(hull[hull_l - 2]);
      if(comp(hull[hull_l - 1], sorted[next])) {
        break;
      }
      --hull_l;
    }
    hull[hull_l] = sorted[next];
    ++hull_l;
    ++next;
  }
  std::vector<entity> res;
  res.resize(hull_l);
  std::copy(hull, hull + hull_l, res.begin());
  return res;
}

std::vector<entity_pair> closest(const std::vector<entity> &H,
                                 const std::vector<entity> &E, int count) {
  std::multimap<int, entity_pair> bests;
  std::vector<entity> O{E};
  for(entity h : H) O.erase(std::find(O.begin(), O.end(), h));
  int H_l = H.size(), E_l = E.size();
  for(int i = 0; i < H_l; ++i) {
    if(H[i].t != entity::type::life) continue;
    for(int j = 0; j < E_l; ++j) {
      if(H[i].t != E[j].t) {
        int d = (H[i].x - E[j].x) * (H[i].x - E[j].x) +
            (H[i].y - E[j].y) * (H[i].y - E[j].y);
        bests.insert({d, {H[i], E[j]}});
        if(bests.size() > count) {
          bests.erase(--bests.end());
        }
      }
    }
  }
  std::vector<entity_pair> res;
  for(auto best : bests) {
    res.push_back(best.second);
  }
  return res;
}

void unit_test() {
}

map best{50, 50};
int best_score = 0;

void search(std::vector<entity> E, int rows, int cols,
            std::vector<entity_pair> pairs, int max_depth) {
  if(!E.empty()) {
    std::vector<entity> hull = convex_hull(E);
    std::vector<entity_pair> ones = closest(hull, E, max_depth > 0 ? 4 : 2);
    for(const entity_pair one : ones) {
      std::vector<entity> next_E{E};
      std::vector<entity_pair> next_pairs{pairs};
      next_pairs.push_back(one);
      next_E.erase(std::find(next_E.begin(), next_E.end(), one.first));
      next_E.erase(std::find(next_E.begin(), next_E.end(), one.second));
      search(next_E, rows, cols, next_pairs, max_depth - 1);
      if(max_depth < -7) break;
    }
  } else {
    map result{rows, cols};
    std::map<int, entity_pair> owners;
    for(const entity_pair &pair : pairs) {
      int owner = result.get_next_owner();
      owners[owner] = pair;
      result.set_owner(pair.first.x, pair.first.y, owner);
      result.set_owner(pair.second.x, pair.second.y, owner);
    }

    for(auto it = owners.rbegin(); it != owners.rend(); ++it) {
      auto ownership = *it;
      int owner = ownership.first;
      entity_pair pair = ownership.second;
      std::vector<std::pair<int, int>> path =
          result.path(pair.first.x, pair.first.y,
                      pair.second.x, pair.second.y);
      if(path.size() == 0) {
        return;
      }
      for(const std::pair<int, int> &point : path) {
        if((point.first != pair.first.x || point.second != pair.first.y) &&
           (point.first != pair.second.x || point.second != pair.second.y)) {
          result.set_owner(point.first, point.second, owner);
        }
      }
    }
    if(result.fill(0, rows, 1, 0, cols, 1) > best_score) {
      best_score = result.get_total_score();
      best = result;
    }
  }
}

int main() {
  UNIT_TESTS();
  int rows, cols, K;
  std::cin >> rows >> cols >> K;
  std::vector<entity> E;
  for(int k = 0; k < K; ++k) {
    int x, y;
    std::cin >> x >> y;
    E.push_back(entity{entity::type::life, x, y});
  }
  for(int k = 0; k < K; ++k) {
    int x, y;
    std::cin >> x >> y;
    E.push_back(entity{entity::type::mana, x, y});
  }

  std::vector<entity_pair> owners;
  for(sMax = 0; sMax <= 1; ++sMax) {
    search(E, rows, cols, owners, 1);
  }

  TRACE_LINE(best_score);
  std::cout << best.toDebugString();
}
