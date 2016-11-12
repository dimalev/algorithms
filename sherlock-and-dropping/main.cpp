#include <iostream>
#include <vector>
#include <algorithm>

class point {
public:
  int x, y;

  static x_comparator(const point &one, const point &two) { return one.x < two.x; }
  static y_comparator(const point &one, const point &two) { return one.y < two.y; }
};

class line {
public:
  point left, right;
  bool is_left;
  line *next = nullptr;
};

bool is_above(const line &in_line, const point &in_point) {
  int a = in_line.right.x - in_line.left.x,
    b = in_line.right.y - in_line.left.y,
    u = in_point.x - in_line.left.x,
    v = in_point.y - in_line.left.y;
  return b * u - a * v < 0;
}

// bool operator<(const point &left, const point &right) {
//   return left.x < right.x;
// }

bool strictly_above(const line &left, const line &right) {
  return is_above(left, right.left) && is_above(left, right.right);
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
  out_line.is_left = out_line.left.y > out_line.right.y;
  return in;
}

void build_tree(std::vector<line> &lines) {
}

int fall_x(std::vector<line> &lines, point& in_point) {
  
}

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<line> lines;
  for(int i = 0; i < n; ++i) {
    line in_line;
    std::cin >> in_line;
    lines.push_back(in_line);
  }
  build_tree(lines);
  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    if(strictly_above(left_close, right_close)) {
    }
  }
}
