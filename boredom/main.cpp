#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <set>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

class rectangle {
public:
  rectangle() {}
  explicit rectangle(int tx, int ty, int bx, int by)
    : tx_{tx}, ty_{ty}, bx_{bx}, by_{by} {}

  std::string str() const {
    std::stringstream ss;
    ss << "(" << tx_ << "," << ty_ << "; " << bx_ << "," << by_ << ")";
    return ss.str();
  }

  rectangle top(int x) {
    rectangle res(tx_, ty_, x, by_); return res;
  }

  rectangle bottom(int x) {
    rectangle res(x, ty_, bx_, by_); return res;
  }

  rectangle left(int y) {
    rectangle res(tx_, ty_, bx_, y); return res;
  }

  rectangle right(int y) {
    rectangle res(tx_, y, bx_, by_); return res;
  }

  int tx() const { return tx_; }
  int ty() const { return ty_; }
  int bx() const { return bx_; }
  int by() const { return by_; }

  bool intersects(const rectangle& other) const {
    return !(other.tx_ > bx_ || other.ty_ > by_ ||
             tx_ > other.bx_ || ty_ > other.by_);
  }

  bool contains(const rectangle& other) const {
    return tx_ <= other.tx_ && ty_ <= other.ty_ &&
      bx_ >= other.bx_ && by_ >= other.by_;
  }

  bool contains(const int& x, const int& y) const {
    return x >= tx_ && x <= bx_ && y >= ty_ && y <= by_;
  }
private:
  int tx_, ty_, bx_, by_;
};

class node {
public:
  explicit node(int x, int y, bool is_horizontal, rectangle bounds)
    : x_{x}, y_{y}, is_horizontal_{is_horizontal}, bounds_{bounds}, size_{1} {
  }

  long long count(const rectangle& rect) {
    if(rect.contains(bounds_)) return size_;
    long long res = rect.contains(x_, y_) ? 1 : 0;
    if(smaller && rect.intersects(smaller->bounds_))
      res += smaller->count(rect);
    if(bigger && rect.intersects(bigger->bounds_))
      res += bigger->count(rect);
    return res;
  }

  int depth() const {
    int res = 1;
    if(smaller) res = smaller->depth() + 1;
    if(bigger) res = std::max(res, bigger->depth() + 1);
    return res;
  }

  void push(int x, int y) {
    ++size_;
    if(is_horizontal_) {
      if(x < x_) {
        if(smaller) smaller->push(x, y);
        else {
          smaller.reset(new node(x, y, true, bounds_.top(x_ - 1)));
        }
      } else {
        if(bigger) bigger->push(x, y);
        else {
          bigger.reset(new node(x, y, true, bounds_.bottom(x_)));
        }
      }
    } else {
      if(y < y_) {
        if(smaller) smaller->push(x, y);
        else {
          smaller.reset(new node(x, y, true, bounds_.left(y_ - 1)));
        }
      } else {
        if(bigger) bigger->push(x, y);
        else {
          bigger.reset(new node(x, y, true, bounds_.right(y_)));
        }
      }
    }
  }

  void pack() {
    std::vector<int> hor, ver;
    hor.push_back(x_);
    ver.push_back(y_);
    if(smaller) {
      smaller->pack();
      hor.push_back(smaller->bounds_.tx());
      hor.push_back(smaller->bounds_.bx());
      ver.push_back(smaller->bounds_.ty());
      ver.push_back(smaller->bounds_.by());
    }
    if(bigger) {
      bigger->pack();
      hor.push_back(bigger->bounds_.tx());
      hor.push_back(bigger->bounds_.bx());
      ver.push_back(bigger->bounds_.ty());
      ver.push_back(bigger->bounds_.by());
    }
    bounds_ = rectangle(*std::min_element(hor.begin(), hor.end()),
                        *std::min_element(ver.begin(), ver.end()),
                        *std::max_element(hor.begin(), hor.end()),
                        *std::max_element(ver.begin(), ver.end()));
  }

  std::string str(std::string prefix) {
    std::stringstream ss;
    ss << prefix << " " << x_ << ", " << y_ << " (" << bounds_.str() << ")\n";
    if(smaller) ss << smaller->str(prefix + "--");
    if(bigger) ss << bigger->str(prefix + "--");
    return ss.str();
  }
private:
  int x_, y_, size_;
  bool is_horizontal_;
  rectangle bounds_;
  std::unique_ptr<node> smaller, bigger;
};

inline long long comb(long long S) {
  return S * (S - 1) / 2;
}

#ifdef UNITS
void unit_tests() {
  test_header("test count");
  int N;
  std::cin >> N;
  node root(0, 0, true, rectangle(0, 0, 200000, 200000));
  fr(i,0,N) {
    int t;
    std::cin >> t;
    if(t == 1) {
      int x, y;
      std::cin >> x >> y;
      root.push(x, y);
    } else {
      int tx, ty, bx, by;
      std::cin >> tx >> ty >> bx >> by;
      rectangle query(tx, ty, bx, by);
      std::cout << root.count(query) << std::endl;
    }
  }
  TRACE_LINE(root.str(""));
}
#endif

void binary_push(const std::vector<std::pair<int, int>> &dots, int start ,
                 int end, node *root) {
  if(start == end) return;
  int mid = (start + end) / 2;
  root->push(dots[mid].first, dots[mid].second);
  binary_push(dots, start, mid, root);
  binary_push(dots, mid + 1, end, root);
}

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  long long N;
  int Q;
  std::cin >> N >> Q;
  std::vector<std::pair<int, int>> D;
  D.resize(N);
  std::set<int> uniq;
  fr(i,0,N) {
    D[i].first = i + 1;
    std::cin >> D[i].second;
    uniq.insert(D[i].second);
  }
  // std::random_shuffle(D.begin(), D.end());
  // node root(D[0].first, D[0].second, true, rectangle(1, 1, N, N));
  // fr(i,1,N) {
  //   root.push(D[i].first, D[i].second);
  // }
  int mid = N / 2;
  node root(D[mid].first, D[mid].second, true, rectangle(1, 1, N, N));
  binary_push(D, 0, mid, &root);
  binary_push(D, mid+1, N, &root);
  root.pack();
  long long t = comb(N);
  fr(i,0,Q) {
    int tx, ty, bx, by;
    std::cin >> tx >> ty >> bx >> by;
    long long c = 0ll;
    if(tx > 1) {
      c += comb(root.count(rectangle(1,1,tx-1,N)));
      if(ty > 1) {
        c -= comb(root.count(rectangle(1,1,tx-1,ty-1)));
      }
      if(by < N) {
        c -= comb(root.count(rectangle(1,by+1,tx-1,N)));
      }
    }
    if(bx < N) {
      c += comb(root.count(rectangle(bx+1,1,N,N)));
      if(ty > 1) {
        c -= comb(root.count(rectangle(bx+1,1,N,ty-1)));
      }
      if(by < N) {
        c -= comb(root.count(rectangle(bx+1,by+1,N,N)));
      }
    }
    if(ty > 1) {
      c += comb(root.count(rectangle(1,1,N,ty-1)));
    }
    if(by < N) {
      c += comb(root.count(rectangle(1,by+1,N,N)));
    }
    std::cout << (t - c) << std::endl;
  }
  // std::cout << root.str("") << std::endl;
  return 0;
}
