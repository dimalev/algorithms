#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#define UNIT_TESTS()

#endif

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(const T x, const T y, int ulp) {
  return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
                         || std::fabs(x-y) < std::numeric_limits<T>::min();
}

class point {
public:
  point() = default;
  point(double x, double y) : x(x), y(y) {}
  double x, y;

  bool operator==(const point &other) {
    return almost_equal(x, other.x, 2) && almost_equal(y, other.y, 2);
  }
  point operator-(const point &other) {
    return point(x - other.x, y - other.y);
  }
};

bool is_not_cw(point * const pivot, point * const from, point * const to) {
  point norm_from = *from - *pivot; // 0 1
  point norm_to = *to - *pivot; // 1 0
  return norm_from.y * norm_to.x <= norm_from.x * norm_to.y;
}

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
  void set_points(point start) {
    create_points();
    *top = start;
    *bottom = start;
    is_ray = true;
    tan = +0.f;
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
    tan = (top->x - bottom->x);
  }
  virtual ~segment() {
    if(is_own_points) {
      delete top; delete bottom;
    }
  }
  point *top, *bottom;
  double tan;
  bool is_ray = false;

  double y_from_x(double in_x) const { return bottom->y; }
  double x_from_y(double in_y) const {
    if(is_ray) return top->x;
    return bottom->x + (top->x - bottom->x) * (in_y - bottom->y) / (top->y - bottom->y);
  }

  bool intersects(const segment * other) const {
    if(is_ray) {
      if(other->is_ray) return false;
      return other->intersects(this);
    }
    if(!other->is_ray) return false;
    if(top->x > bottom->x) {
      if(other->top->x > top->x) return false;
      if(other->top->x < bottom->x) return false;
      return is_not_cw(bottom, top, other->top);
    }
    if(other->top->x > bottom->x) return false;
    if(other->top->x < top->x) return false;
    return is_not_cw(top, bottom, other->top);
  }
};

std::istream &operator>>(std::istream &in, segment &out_segment) {
  point one, two;
  in >> one >> two;
  if(one == two) out_segment.set_points(one);
  else out_segment.set_points(one, two);
  return in;
}

class scan_line {
public:
  explicit scan_line(double y) : y(y) {}
  double y;

  bool less(segment *left, segment *right) {
    double left_x = left->x_from_y(y),
      right_x = right->x_from_y(y);
    if(almost_equal(left_x, right_x, 2))
      return left->tan < right->tan;
    return left_x < right_x;
  }
};

void segment_test() {
  int T;
  // tangents
  std::cin >> T;
  while(T--) {
    segment testable;
    std::cin >> testable;
    if(testable.tan > +0.f) std::cout << "+1\n";
    else if(testable.tan < -0.f) std::cout << "-1\n";
    else std::cout << "0\n";
  }
  std::cin >> T;
  while(T--) {
    segment testable;
    double y;
    std::cin >> y >> testable;
    std::cout << std::setprecision(2) << testable.x_from_y(y) << "\n";
  }
}

void scan_line_test() {
  int T;
  std::cin >> T;
  while(T--) {
    segment one, two;
    double y;
    std::cin >> y >> one >> two;
    if(scan_line(y).less(&one, &two)) std::cout << "true\n";
    else std::cout << "false\n";
  }
}

void test_cw() {
  int T;
  std::cin >> T;
  while(T--) {
    point pivot, from, to;
    std::cin >> pivot >> from >> to;
    if(is_not_cw(&pivot, &from, &to)) std::cout << "true\n";
    else std::cout << "false\n";
  }
}

void test_intersection() {
}

void unit_tests() {
  segment_test();
  scan_line_test();
  test_cw();
  test_intersection();
}

int main() {
  UNIT_TESTS()
  return 0;
}
