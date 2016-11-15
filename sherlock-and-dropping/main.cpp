#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class point {
public:
  int x, y;

  static bool x_comparator(const point &one, const point &two) { return one.x > two.x; }
  static bool y_comparator(const point &one, const point &two) { return one.y > two.y; }
};

class line {
public:
  point top, bottom;
  bool is_left;
  int final_x;
};

bool is_above(const line &in_line, const point &in_point) {
  int a = in_line.top.x - in_line.bottom.x,
    b = in_line.top.y - in_line.bottom.y,
    u = in_point.x - in_line.top.x,
    v = in_point.y - in_line.top.y;
  return in_line.is_left ? (b * u - a * v < 0) : (b * u - a * v > 0);
}

bool bottom_x_comparator(const line &one, const line &two) {
  return (is_above(two, one.top) && is_above(two, one.bottom));
}

// bool strictly_above(const line &left, const line &right) {
//   return is_above(left, right.left) && is_above(left, right.right);
// }

std::istream& operator>>(std::istream &in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::ostream& operator<<(std::ostream &out, const point &out_point) {
  out << out_point.x << " " << out_point.y;
  return out;
}

std::istream& operator>>(std::istream &in, line &out_line) {
  point left, right;
  in >> left >> right;
  if(left.y < right.y) {
    out_line.bottom = left;
    out_line.top = right;
  } else {
    out_line.bottom = right;
    out_line.top = left;
  }
  out_line.is_left = out_line.top.x > out_line.bottom.x;
  return in;
}

std::ostream& operator<<(std::ostream &out, const line &out_line) {
  out << out_line.top << " " << out_line.bottom;
  return out;
}

int fall_x(std::vector<line> &lines, point& in_point) {
  auto it = std::lower_bound(lines.begin(), lines.end(), in_point.y, [](const line &l, int y) -> bool { return l.bottom.y > y; });
  while(it != lines.end()) {
    if(it->is_left) {
      if(it->top.x < in_point.x || it->bottom.x > in_point.x) {
        ++it;
        continue;
      }
    } else {
      if(it->top.x > in_point.x || it->bottom.x < in_point.x) {
        ++it;
        continue;
      }
    }
    if(is_above((*it), in_point)) {
      return it->final_x;
    }
    ++it;
  }
  return in_point.x;
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
  //  std::copy(lines.begin(), lines.end(), std::ostream_iterator<line>(std::cout, "\n"));
  //  std::cout << "\n";
  std::sort(lines.begin(), lines.end(), bottom_x_comparator);
  //  std::copy(lines.begin(), lines.end(), std::ostream_iterator<line>(std::cout, "\n"));

  auto it = lines.rbegin();
  while(it != lines.rend()) {
    it->final_x = fall_x(lines, it->bottom);
    ++it;
  }

  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    std::cout << fall_x(lines, in_point) << std::endl;
  }
}
