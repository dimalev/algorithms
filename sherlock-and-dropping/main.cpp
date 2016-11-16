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

  inline point bottom() const { return start.y > end.y ? end : start; }
  inline point top() const { return start.y < end.y ? end : start; }

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
  int a = in_line->bottom().x - in_line->top().x,
    b = in_line->bottom().y - in_line->top().y,
    u = in_point.x - in_line->bottom().x,
    v = in_point.y - in_line->bottom().y;
  if(in_line->is_left()) return b * u - a * v < 0;
  else return b * u - a * v > 0;
}

bool is_line_below(const line *one, const line *two) {
  return (is_point_above(two, one->start) && is_point_above(two, one->end)) ||
    (!is_point_above(one, two->start) && !is_point_above(one, two->end));
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
  return one->bottom().y > two->bottom().y;
}

class forest {
public:
  std::vector<line*> lefts;
  std::vector<line*> rights;

  const line* get_falling(const point &in_point) const {
    auto left_it = lefts.rbegin();
    auto right_it = rights.rbegin();
    while(left_it != lefts.rend()) {
      if(falls_on(*left_it, in_point)) break;
      ++left_it;
    }
    while(right_it != rights.rend()) {
      if(falls_on(*right_it, in_point)) break;
      ++right_it;
    }
    if(left_it == lefts.rend() && right_it == rights.rend()) {
      return nullptr;
    } else if(left_it == lefts.rend()) {
      return *right_it;
    } else if(right_it == rights.rend()) {
      return *left_it;
    } else {
      if(is_line_above(*left_it, *right_it) || is_line_below(*right_it, *left_it)) {
        return *left_it;
      } else {
        return *right_it;
      }
    }
  }

  void sort() {
    std::sort(lefts.begin(), lefts.end(), is_line_above);
    std::sort(rights.begin(), rights.end(), is_line_above);

    std::vector<line*> all = lefts;
    all.insert(all.end(), rights.begin(), rights.end());

    std::sort(all.begin(), all.end(), bottom_y_comparator);

    auto it = all.rbegin();
    while(it != all.rend()) {
      const line *fall = get_falling((*it)->bottom());
      if(fall == nullptr) {
        (*it)->final_x = (*it)->bottom().x;
        // std::cout << (*it) << " falls on itself" << std::endl;
      } else {
        (*it)->final_x = fall->final_x;
        // std::cout << (*it) << " falls on " << fall << std::endl;
      }
      ++it;
    }

    // std::copy(all.begin(), all.end(), std::ostream_iterator<line*>(std::cout, "\n"));
  }
};

int main() {
  int n, q;
  std::cin >> n >> q;
  forest lines;
  for(int i = 0; i < n; ++i) {
    line* in_line = new line;
    std::cin >> *in_line;
    if(in_line->is_left()) lines.lefts.push_back(in_line);
    else lines.rights.push_back(in_line);
  }
  lines.sort();
  // std::copy(lines.lefts.begin(), lines.lefts.end(), std::ostream_iterator<line*>(std::cout, "\n"));
  // std::cout << std::endl;
  // std::copy(lines.rights.begin(), lines.rights.end(), std::ostream_iterator<line*>(std::cout, "\n"));
  for(int i = 0; i < q; ++i) {
    point in_point;
    std::cin >> in_point;
    const line *fall = lines.get_falling(in_point);
    if(nullptr == fall) {
      std::cout << in_point.x << std::endl;
    }
    else {
      // std::cout << in_point << " falls on " << fall << std::endl;
      std::cout << fall->final_x << std::endl;
    }
  }
  return 0;
}
