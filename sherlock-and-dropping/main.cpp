#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

class point {
public:
  double x, y;
};

std::istream& operator>>(std::istream &in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::ostream& operator<<(std::ostream &out, const point &in_point) {
  out << in_point.x << " " << in_point.y;
  return out;
}

class segment {
  bool is_own_points = false;
  void create_points() {
    is_own_points = true;
    top = new point;
    bottom = new point;
  }
public:
  explicit segment() = default;
  explicit segment(point *start) : top(start), tan(+0.f) {} // simple ray constructor
  segment(point *start, point *end) {
    if(start->y > end->y) {
      top = start; bottom = end;
    } else {
      bottom = start; top = end;
    }
    update_tan();
  }
  void set_points(point start, point end) {
    create_points();
    if(start.y > end.y) {
      *top = start; *bottom = end;
    } else {
      *bottom = start; *top = end;
    }
    update_tan();
  }
  void update_tan() {
    tan = (top->y - bottom->y) / (top->x - bottom->x);
  }
  virtual ~segment() {
    if(is_own_points) {
      delete top; delete bottom;
    }
  }
  point *top, *bottom;
  double tan;
  bool is_ray;

  double y_from_x(double in_x) { return bottom->y; }
  double x_from_y(double in_y) { return bottom->x; }
};

std::istream &operator>>(std::istream &in, segment &out_segment) {
  point one, two;
  in >> one >> two;
  out_segment.set_points(start, end);
}

class scan_line {
public:
  double y;

  bool less(segment *left, segment *right) {
    return true;
  }
};

void segment_test() {
  int T;
  // tangents
  std::cin >> T;
  while(T--) {
    segment testable;
    std::cin >> testable;
    if(testable.tan
  }
}

void scan_line_test() {
}

void unit_tests() {
  segment_test();
  scan_line_test();
}

int main() {
  UNIT_TESTS()
  return 0;
}
