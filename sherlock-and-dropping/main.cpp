#include <iostream>

inline void swap(int &a, int &b) { int t = a; a = b; b = t; }

class point {
public:
  int x, y;
};

class line {
public:
  point left, right;
  bool is_left;
};

bool is_above(const line &in_line, const point &in_point) {
  int a = in_line.right.x - in_line.left.x,
    b = in_line.right.y - in_line.left.y,
    u = in_point.x - in_line.left.x,
    v = in_point.y - in_line.left.y;
  return b * u - a * v < 0;
}

bool operator<(const point &left, const point &right) {
  return left.x < right.x;
}

bool strictly_above(const line &left, const line &right) {
  return is_above(left, right.left) && is_above(left, right.right);
}

bool operator<(const line &left, const line &right) {
  return isAbove(left, right.left);
}

std::istream& operator>>(std::istream &in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::istream& operator>>(std::istream &in, line &out_line) {
  point left, right;
  in >> left >> right;
  if(left < right) {
    out_line.left = left;
    out_line.right = right;
  } else {
    out_line.left = right;
    out_line.right = left;
  }
  out_line.is_left = out_line.left.y > out_lint.right.y;
  return in;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  vector<line> lefts, rights;
  for(int i = 0; i < n; ++i) {
    line in_line;
    std::cin >> in_line;
    if(in_line.is_left) lefts.push_back(in_line);
    else rights.push_back(in_line);
  }
  std::sort(lefts.begin(), lefts.end());
  std::sort(rights.begin(), rights.end());
  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    left_close = std::lower_bound(lefts.begin(), lefts.end(), in_point, is_above);
    right_close = std::lower_bound(rights.begin(), rights.end(), in_point, is_above);
    if(strictly_above(left_close, right_close)) {
    }
  }
}
