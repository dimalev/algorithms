#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <vector>
#include <set>

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

bool is_ccw(point * const pivot, point * const from, point * const to) {
  point norm_from = *from - *pivot; // 0 1
  point norm_to = *to - *pivot; // 1 0
  return norm_from.y * norm_to.x < norm_from.x * norm_to.y;
}

bool is_cw(point * const pivot, point * const from, point * const to) {
  point norm_from = *from - *pivot; // 0 1
  point norm_to = *to - *pivot; // 1 0
  return norm_from.y * norm_to.x > norm_from.x * norm_to.y;
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
  explicit segment(point *start) : top(start), bottom(start), tan(+0.f), is_ray(true) {} // simple ray constructor
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
      // delete top; delete bottom;
    }
  }
  point *top, *bottom;
  double final_x;
  double tan;
  bool is_ray = false;

  // ray created by segment
  segment *owner = nullptr;

  // ray finish data
  class event *end_event = nullptr;
  segment *intersector = nullptr;

  double x_from_y(double in_y) const {
    if(is_ray) return top->x;
    return bottom->x + (top->x - bottom->x) * (in_y - bottom->y) / (top->y - bottom->y);
  }

  double y_from_x(double in_x) const {
    return bottom->y + (top->y - bottom->y) * (in_x - bottom->x) / (top->x - bottom->x);
  }

  bool operator<(const segment &other) const {
    if(other.is_ray) {
      if(is_ray) {
        if(other.top->x == top->x) return top->y > other.top->y;
        return top->x < other.top->x;
      }
      if(other.top->x <= std::min(top->x, bottom->x)) return false;
      if(other.top->x >= std::max(top->x, bottom->x)) return true;
      if(top->x < bottom->x) return !is_cw(top, bottom, other.top);
      return is_cw(bottom, top, other.top);
    }
    if(is_ray) return !(other < *this);
    if(other.top->y > top->y) return !(other < *this);
    if(top->x < bottom->x) return !is_cw(top, bottom, other.top);
    return is_cw(bottom, top, other.top);
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
      return !is_cw(bottom, top, other->top);
    }
    if(other->top->x > bottom->x) return false;
    if(other->top->x < top->x) return false;
    return !is_cw(top, bottom, other->top);
  }
};

std::istream &operator>>(std::istream &in, segment &out_segment) {
  point one, two;
  in >> one >> two;
  if(one == two) out_segment.set_points(one);
  else out_segment.set_points(one, two);
  return in;
}

std::ostream &operator<<(std::ostream &out, const segment &in_segment) {
  out << (in_segment.is_ray ? "R " : "S ") << *in_segment.top << " " << *in_segment.bottom;
  return out;
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

class event {
public:
  enum class type { begin, end };
  event(type t, segment *who, point *where, bool own_point = false) : t(t), who(who), where(where), is_own_point(own_point) {}
  ~event() {
    // if(is_own_point) delete where;
  }
  type t;
  segment *who;
  point *where;
  bool is_own_point;

  bool operator<(const event &other) {
    if(other.where->y > where->y) return false;
    if(other.where->y < where->y) return true;
    if(other.t == type::end && t == type::begin) return false;
    if(other.t == type::begin && t == type::end) return true;
    return who->is_ray;
  }
};

std::ostream& operator<<(std::ostream &out, const event &in_event) {
  out << (in_event.t == event::type::begin ? "[begin " : "[end ");
  out << "(" << *in_event.who << ") at (" << *in_event.where << ")]";
  return out;
}

class intersection {
public:
  intersection(segment *r, segment *s) : r(r), s(s) {}
  const segment *r, *s;
};

class segment_pointer_comparator {
public:
  bool operator()(segment *left, segment *right) { return *left < *right; }
};

class event_pointer_comparator {
public:
  bool operator()(event *left, event *right) { return *left < *right; }
};

class find_intersections {
  std::vector<intersection*> intersections;
  std::set<event*, event_pointer_comparator> events;
  std::set<event*, event_pointer_comparator> ray_ends;
  std::set<segment*, segment_pointer_comparator> segments;

  void register_intersection(segment *one, segment *two) {
    segment *r = one->is_ray ? one : two;
    segment *s = one->is_ray ? two : one;
    TRACE_LINE("---- Preregister intersection of ray " << *r << " and segment " << *s);
    double intersection_y = s->y_from_x(r->top->x);
    if(r->end_event == nullptr) {
      event *ray_end = new event(event::type::end, r, new point(r->top->x, intersection_y), true);
      ray_ends.insert(ray_end);
      r->end_event = ray_end;
      r->intersector = s;
    } else {
      if(intersection_y > r->end_event->where->y) {
        ray_ends.erase(r->end_event);
        r->end_event->where->y = intersection_y;
        r->intersector = s;
        ray_ends.insert(r->end_event);
      }
    }
  }

public:
  std::vector<intersection*> operator()(std::vector<segment*> &bars, std::vector<segment*> &balls) {
    intersections.clear();
    events.clear();
    ray_ends.clear();
    segments.clear();
    TRACE_LINE("---- (01) Building segments " << bars.size());
    for(segment* bar : bars) {
      events.emplace(new event(event::type::begin, bar, bar->top));
      events.emplace(new event(event::type::end, bar, bar->bottom));
    }
    TRACE_LINE("---- (02) Adding rays " << balls.size());
    for(segment* ball : balls)
      events.emplace(new event(event::type::begin, ball, ball->top));
    TRACE_LINE("---- (03) Walk through events");
    while(events.size() > 0) {
      if(ray_ends.size() > 0 && **ray_ends.begin() < **events.begin()) {
        event* ray_end = *ray_ends.begin();
        TRACE_LINE("---- " << *ray_end);
        ray_ends.erase(ray_ends.begin());
        TRACE_LINE("---- Put intersection of ray " << *ray_end->who << " and segment " << *ray_end->who->intersector);
        intersections.push_back(new intersection(ray_end->who, ray_end->who->intersector));
        segments.erase(ray_end->who);
        // delete ray_end;
      } else {
        event *e = *events.begin();
        TRACE_LINE("---- " << *e);
        events.erase(events.begin());
        if(e->t == event::type::begin) {
          std::pair<std::set<segment*>::iterator, bool> inserted = segments.insert(e->who);
          if(next(inserted.first) != segments.end()) {
            segment *bigger = *next(inserted.first);
            if(bigger->intersects(e->who))
              register_intersection(bigger, e->who);
          }
          if(inserted.first != segments.begin()) {
            segment *smaller = *prev(inserted.first);
            if(smaller->intersects(e->who))
              register_intersection(smaller, e->who);
          }
        } else {
          std::set<segment*>::iterator place_it = segments.find(e->who);
          ASSERT(place_it != segments.end());
          if(place_it != segments.begin() && next(place_it) != segments.end()) {
            segment *bigger = *next(place_it);
            segment *smaller = *prev(place_it);
            if(bigger->intersects(smaller))
              register_intersection(bigger, smaller);
          }
          segments.erase(place_it);
        }
      }
    }
    return intersections;
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
  std::cin >> T;
  while(T--) {
    segment testable;
    double x;
    std::cin >> x >> testable;
    std::cout << std::setprecision(2) << testable.y_from_x(x) << "\n";
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
    if(!is_cw(&pivot, &from, &to)) std::cout << "true\n";
    else std::cout << "false\n";
  }
}

void test_intersection() {
  int T;
  std::cin >> T;
  while(T--) {
    segment one, two;
    std::cin >> one >> two;
    std::cout << (one.intersects(&two)? "true\n" : "false\n");
  }
}

void test_segment_order() {
  int T;
  std::cin >> T;
  segment_pointer_comparator comparator;
  while(T--) {
    segment one, two;
    std::cin >> one >> two;
    ASSERT(comparator(&one, &two) != comparator(&two, &one))
    std::cout << (comparator(&one, &two) ? "less\n" : "not less\n");
  }
}

void unit_tests() {
  segment_test();
  scan_line_test();
  test_cw();
  test_intersection();
  test_segment_order();
}

int main() {
  UNIT_TESTS();
  int N, M;
  std::cin >> N >> M;
  std::vector<segment*> segments;
  segments.reserve(N);
  std::vector<segment*> rays;
  rays.reserve(N);
  TRACE_LINE("(01) Reading segments");
  for(int i = 0; i < N; ++i) {
    segment *new_segment = new segment();
    std::cin >> *new_segment;
    segments.push_back(new_segment);
    new_segment->final_x = new_segment->bottom->x;
    segment *segment_ray = new segment(new_segment->bottom);
    segment_ray->owner = new_segment;
    rays.push_back(segment_ray);
  }
  TRACE_LINE("(02) Searching falls");
  find_intersections ray_finder;
  std::vector<intersection*> ray_falls = ray_finder(segments, rays);
  for(auto inter_rit = ray_falls.rbegin(); inter_rit != ray_falls.rend(); ++inter_rit) {
    (*inter_rit)->r->owner->final_x = (*inter_rit)->r->intersector->final_x;
  }
  rays.clear();
  rays.reserve(M);
  TRACE_LINE("(03) Reading balls");
  for(int i = 0; i < M; ++i) {
    point *ball = new point;
    std::cin >> *ball;
    segment *projectile = new segment(ball);
    rays.push_back(projectile);
  }
  TRACE_LINE("(04) Searching ball falls");
  ray_falls = ray_finder(segments, rays);
  TRACE_LINE("(05) Outputting data");
  for(auto ray : rays) {
    if(ray->intersector == nullptr) std::cout << ray->top->x << "\n";
    std::cout << ray->intersector->final_x << "\n";
  }
  return 0;
}
