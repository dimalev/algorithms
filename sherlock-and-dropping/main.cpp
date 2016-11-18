#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct point {
  int x, y;
};

struct line {
  point start, end;
  point top, bottom;
  int final_x;

  // \
  //  \  <- left line
  //   \
  //
  // start = (0, 3) end = (3, 0)
  // start = (3, 0) end = (0, 3)
  inline bool is_left() const { return (start.x < end.x) == (start.y > end.y); }
};

std::istream& operator>>(std::istream& in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::istream& operator>>(std::istream& in, line &out_line) {
  in >> out_line.start >> out_line.end;
  if(out_line.start.y > out_line.end.y) {
    out_line.top = out_line.start;
    out_line.bottom = out_line.end;
  } else {
    out_line.top = out_line.end;
    out_line.bottom = out_line.start;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const point &in_point) {
  out << in_point.x << ", " << in_point.y;
  return out;
}

std::ostream& operator<<(std::ostream& out, const line &in_line) {
  out << "[(" << in_line.start << ") (" << in_line.end << ") (" << in_line.final_x << ")]";
  return out;
}

std::ostream& operator<<(std::ostream& out, const line *in_line) {
  out << "[(" << in_line->start << ") (" << in_line->end << ") (" << in_line->final_x << ")]";
  return out;
}

bool is_point_above(const line *in_line, const point &in_point) {
  long long a = in_line->bottom.x - in_line->top.x,
    b = in_line->bottom.y - in_line->top.y,
    u = in_point.x - in_line->bottom.x,
    v = in_point.y - in_line->bottom.y;
  if(in_line->is_left()) return b * u <= a * v;
  return b * u >= a * v;
}

bool is_line_above(const line *one, const line *two) {
  return (is_point_above(one, two->start) && is_point_above(one, two->end)) ||
    (!is_point_above(two, one->start) && !is_point_above(two, one->end));
}

bool falls_on(const line *in_line, const point &in_point) {
  if(in_point.x < std::min(in_line->start.x, in_line->end.x) ||
     in_point.x > std::max(in_line->start.x, in_line->end.x)) return false;
  // std::cout << in_point << " can fall on " << (*in_line) << std::endl;
  return is_point_above(in_line, in_point);
}

bool bottom_y_comparator(const line *one, const line *two) {
  return one->bottom.y > two->bottom.y;
}

bool bottom_y_test(const point &in_point, const line *in_line) { return in_line->bottom.y < in_point.y; }

bool is_closer(const line *new_line, const line *old_line, const point &in_point) {
  long long dx1 = new_line->bottom.x - new_line->top.x,
    dy1 = new_line->bottom.y - new_line->top.y,
    ddx1 = in_point.x - new_line->top.x,
    dx2 = old_line->bottom.x - old_line->top.x,
    dy2 = old_line->bottom.y - old_line->top.y,
    ddx2 = in_point.x - old_line->top.x;
  return ddx1 * dy1 / dx1 + new_line->top.y > ddx2 * dy2 / dx2 + old_line->top.y;
}

const line* get_fall(std::vector<line*> &lines, const point &in_point) {
  auto start = std::upper_bound(lines.begin(), lines.end(), in_point, bottom_y_test);
  const line *result = nullptr;
  while(start != lines.end()) {
    if(falls_on(*start, in_point)) {
      if(result == nullptr || is_closer(*start, result, in_point)) result = *start;
    }
    ++start;
  }
  return result;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<line*> lines;
  for(int i = 0; i < n; ++i) {
    line* in_line = new line;
    std::cin >> *in_line;
    lines.push_back(in_line);
  }
  std::sort(lines.begin(), lines.end(), bottom_y_comparator);
  auto process_it = lines.rbegin();
  while(process_it != lines.rend()) {
    const line *fall = get_fall(lines, (*process_it)->bottom);
    if(fall == nullptr) (*process_it)->final_x = (*process_it)->bottom.x;
    else (*process_it)->final_x = fall->final_x;
    ++process_it;
  }
  // std::copy(lines.begin(), lines.end(), std::ostream_iterator<line*>(std::cout, "\n"));
  // std::cout << std::endl;
  // std::copy(lines.rights.begin(), lines.rights.end(), std::ostream_iterator<line*>(std::cout, "\n"));
  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    const line *fall = get_fall(lines, in_point);
    if(fall == nullptr) {
      std::cout << in_point.x << std::endl;
    }
    else {
      // std::cout << in_point << " falls on " << fall << std::endl;
      std::cout << fall->final_x << std::endl;
    }
  }
  return 0;
}
