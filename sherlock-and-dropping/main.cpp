#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct point {
  int x, y;
};

struct line {
  point start, end;
  int final_x;

  // \
  //  \  <- left line
  //   \
  //
  // start = (0, 3) end = (3, 0)
  // start = (3, 0) end = (0, 3)
  bool is_left() const { return (start.x < end.x) == (start.y > end.y); }
};

bool is_point_above(const line &in_line, const point &in_point) {
  int a = in_line.start.x - in_line.end.x,
    b = in_line.start.y - in_line.end.y,
    u = in_point.x - in_line.start.x,
    v = in_point.y - in_line.start.y;
  if(in_line.start.x > in_line.end.x) return b * u - a * v > 0;
  else return b * u - a * v < 0;
}

bool is_line_above(const line &one, const line &two) {
  return (is_point_above(one, two.start) && is_point_above(one, two.end)) ||
    (!is_point_above(two, one.start) && !is_point_above(two, one.end));
}

bool falls_on(const line &in_line, const point &in_point) {
  if(in_point.x < std::min(in_line.start.x, in_line.end.x) ||
     in_point.x > std::max(in_line.start.x, in_line.end.x)) return false;
  return is_point_above(in_line, in_point);
}

class forest {
public:
  std::vector<line> lefts;
  std::vector<line> rights;

  void sort() {
    std::sort(lefts.begin(), lefts.end(), is_line_above);
    std::sort(rights.begin(), rights.end(), is_line_above);
  }
};

std::istream& operator>>(std::istream& in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::istream& operator>>(std::istream& in, line &out_line) {
  in >> out_line.start >> out_line.end;
  return in;
}

std::ostream& operator<<(std::ostream& out, const point &in_point) {
  out << in_point.x << ", " << in_point.y;
  return out;
}

std::ostream& operator<<(std::ostream& out, const line &in_line) {
  out << "[(" << in_line.start << ") (" << in_line.end << ")]";
  return out;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  forest lines;
  for(int i = 0; i < n; ++i) {
    line in_line;
    std::cin >> in_line;
    if(in_line.is_left()) lines.lefts.push_back(in_line);
    else lines.rights.push_back(in_line);
  }
  lines.sort();
  // std::copy(lines.lefts.begin(), lines.lefts.end(), std::ostream_iterator<line>(std::cout, "\n"));
  // std::cout << std::endl;
  // std::copy(lines.rights.begin(), lines.rights.end(), std::ostream_iterator<line>(std::cout, "\n"));
  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    auto left_it = lines.lefts.begin();
    auto right_it = lines.rights.begin();
    while(left_it != lines.lefts.end()) {
      if(falls_on(*left_it, in_point)) break;
      ++left_it;
    }
    while(right_it != lines.rights.end()) {
      if(falls_on(*right_it, in_point)) break;
      ++right_it;
    }
    if(left_it == lines.lefts.end() && right_it == lines.rights.end()) {
      std::cout << in_point.x << std::endl;
    } else if(left_it == lines.lefts.end()) {
      std::cout << right_it->final_x << std::endl;
    } else if(right_it == lines.rights.end()) {
      std::cout << left_it->final_x << std::endl;
    } else {
      if(is_line_above(*left_it, *right_it)) {
        std::cout << left_it->final_x << std::endl;
      } else {
        std::cout << right_it->final_x << std::endl;
      }
    }
  }
  return 0;
}
