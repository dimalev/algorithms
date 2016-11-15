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
  const line *next = nullptr;
  int final_x;

  static bool bottom_x_comparator(const line &one, const line &two) {
    if(one.bottom.y == two.bottom.y) return one.top.y > two.top.y;
    return one.bottom.y > two.bottom.y;
  }
};

bool is_above(const line &in_line, const point &in_point) {
  int a = in_line.top.x - in_line.bottom.x,
    b = in_line.top.y - in_line.bottom.y,
    u = in_point.x - in_line.top.x,
    v = in_point.y - in_line.top.y;
  return in_line.is_left ? (b * u - a * v < 0) : (b * u - a * v > 0);
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

int fall_x(std::vector<line> &lines, point& in_point, const line* fall_on) {
  fall_on = nullptr;
  for(const line &segment : lines) {
    if(segment.bottom.y >= in_point.y) continue;
    if(segment.is_left) {
      if(segment.top.x < in_point.x) continue;
      if(segment.bottom.x > in_point.x) continue;
    } else {
      if(segment.top.x > in_point.x) continue;
      if(segment.bottom.x < in_point.x) continue;
    }
    if(is_above(segment, in_point)) {
      fall_on = &segment;
      return segment.final_x;
    }
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
  std::sort(lines.begin(), lines.end(), line::bottom_x_comparator);
  //  std::copy(lines.begin(), lines.end(), std::ostream_iterator<line>(std::cout, "\n"));

  auto it = lines.rbegin();
  while(it != lines.rend()) {
    const line *fall_on = nullptr;
    int final_x = fall_x(lines, it->bottom, fall_on);
    if(fall_on == nullptr) {
      it->final_x = final_x; // meh, really just to use fall_x result;
      //TRACE_LINE("line " << (*it) << " falls completely down")
    } else {
      it->next = fall_on;
      it->final_x = fall_on->final_x;
    }
    ++it;
  }

  for(int i = 0; i < q; ++i) {
    point in_point;
    const line *dummy_line = nullptr;
    std::cin >> in_point;
    std::cout << fall_x(lines, in_point, dummy_line) << std::endl;
  }
}
