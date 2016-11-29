#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <iomanip>

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
  point() : x(0), y(0) {}
  point(double x, double y) : x(x), y(y) {}
  double x, y;

  point operator-(const point &another) const {
    return point(x - another.x, y - another.y);
  }

  static int x_comp(const point &left, const point &right) {
    if(left.x == right.x) return 0;
    if(left.x < right.x) return 1;
    return -1;
  }
  static int y_comp(const point &left, const point &right) {
    if(left.y == right.y) return 0;
    if(left.y < right.y) return 1;
    return -1;
  }
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
public:
  segment() {}
  segment(double sx, double sy, double ex, double ey) {
    create_points();
    start->x = sx; start->y = sy;
    end->x = ex; end->y = ey;
  }
  segment(point *start, point*end) : start(start), end(end) {}
  point *start, *end;
  int drop_x;
  void create_points() { start = new point; end = new point; }

  long double dot(const point &another) const {
    point norm_me = *end - *start, // x=0, y=1 vertical up
      norm_she = another - *start; // x=1, y=0 horizontal right
    // 1 * 1 - 0 * 0
    // TRACE_LINE(std::setprecision(2) << norm_me << " " << norm_she);
    return
      static_cast<long double>(norm_me.y) * static_cast<long double>(norm_she.x) -
      static_cast<long double>(norm_me.x) * static_cast<long double>(norm_she.y);
  }

  bool is_clockwise(const point &another) const {
    return dot(another) > 0;
  }

  bool is_below(const point &another) const {
    if(start->x < end->x) return is_clockwise(another);
    else return !is_clockwise(another);
    // return is_clockwise(another);
  }

  bool rough_inside(const point &another) const {
    return another.x >= std::min(start->x, end->x) && another.x <= std::max(start->x, end->x) &&
      another.y >= std::min(start->y, end->y) && another.y <= std::max(start->y, end->y);
  }

  bool intersects(const segment &another) const {
    long double d0 = dot(*another.start),
      d1 = dot(*another.end),
      d2 = another.dot(*start),
      d3 = another.dot(*end);
    // TRACE_LINE(std::setprecision(2) << d0 << " " << d1 << " " << d2 << " " << d3);
    if(((d0 < -0.0001 && d1 > 0.0001) || (d0 > 0.0001 && d1 < -0.0001)) &&
       ((d2 < -0.0001 && d3 > 0.0001) || (d2 > 0.0001 && d3 < -0.0001))) return true;
    if(abs(d0) <= 0.001 && rough_inside(*another.start)) return true;
    if(abs(d1) <= 0.001 && rough_inside(*another.end)) return true;
    if(abs(d2) <= 0.001 && another.rough_inside(*start)) return true;
    if(abs(d3) <= 0.001 && another.rough_inside(*end)) return true;
    return false;
  }

  double y_from_x(int x) const {
    int dx = x - start->x,
      dX = end->x - start->x,
      dY = end->y - start->y;
    return static_cast<double>(dx) / dX * dY + start->y;
  }

  double x_from_y(double y) const {
    int dy = y - start->y,
      dY = end->y - start->y,
      dX = end->x - start->x;
    return static_cast<double>(dy) / dY * dX + start->x;
  }
};

std::istream& operator>>(std::istream &in, segment &out_segment) {
  out_segment.create_points();
  point one, two;
  in >> one >> two;
  if(one.y < two.y) {
    out_segment.start = new point(two);
    out_segment.end = new point(one);
  } else {
    out_segment.start = new point(one);
    out_segment.end = new point(two);
  }
  out_segment.drop_x = out_segment.end->x;
  return in;
}

std::ostream& operator<<(std::ostream &out, const segment &in_segment) {
  out << *in_segment.start << " " << *in_segment.end;
  return out;
}

class ray { // we gona work with vertical only
public:
  ray() {}
  ray(double x, double y) : start(new point(x, y)) {}
  ray(point *start) : start(start) {}
  ray(segment *owner) : is_owner_segment(true), owning_segment(owner), start(owner->end) {}
  point *start; // we will use end to eventually remove ray
  bool is_owner_segment = false;
  segment *owning_segment, *intersected_segment;
  int index; // that is how we are going to report answer!
  point *intersection = nullptr;

  bool intersects(const segment &another) const {
    if(another.end->y > start->y) return false;
    if(start->x < std::min(another.start->x, another.end->x)) return false;
    if(start->x > std::max(another.start->x, another.end->x)) return false;
    if(intersection == nullptr) {
      point *end = new point(start->x, -1000001);
      if(another.intersects(segment(start, end))) {
        delete end; return true;
      }
      delete end; return false;
    }
    return another.intersects(segment(start, intersection));
  }
};

std::ostream& operator<<(std::ostream &out, const ray &in_ray) {
  out << *in_ray.start;
  return out;
}

bool is_point_left(const point &p, const class adapter &a);

class adapter {
public:
  explicit adapter(segment *in_segment) :is_ray(false), s(in_segment) {}
  explicit adapter(ray *in_ray) : is_ray(true), r(in_ray) {}

  bool is_ray;
  segment *s;
  ray *r;

  bool operator==(segment *in_segment) const { return !is_ray && s == in_segment; }
  bool operator==(ray *in_ray) const { return is_ray && r == in_ray; }

  bool intersects(const adapter &other) const {
    if(is_ray == other.is_ray) return false;
    segment *s = is_ray ? other.s : this->s;
    ray *r = is_ray ? this->r : other.r;
    return r->intersects(*s);
  }

  bool intersects(const ray &in_ray) const {
    if(is_ray) return false;
    return in_ray.intersects(*s);
  }

  bool intersects(const segment &in_segment) const {
    if(!is_ray) return false;
    return r->intersects(in_segment);
  }
};

bool is_point_left(const point &p, const adapter &a) {
  if(a.is_ray) {
    if(p.x < a.r->start->x) return true;
    if(p.x > a.r->start->x) return false;
    return p.y < a.r->start->y;
  }
  // if(a.s->start->x < a.s->end->x) return a.s->is_clockwise(p);
  return a.s->is_clockwise(p);
}

class intersection {
public:
  intersection(ray* who, segment *where) : who(who), where(where) {}
  intersection(ray* who) : who(who), where(who->intersected_segment) {}
  ray* who;
  segment *where;
};

class event {
public:
  enum class types { start, end };

  event(types type, segment *s, point *p) : type(type), s(s), p(p) {}
  event(ray *r) : is_ray(true), type(types::start), r(r), p(r->start) {}
  event(types type, ray *r, point *p) : is_ray(true), type(type), r(r), p(p) {}

  bool is_ray = false;
  types type;
  segment *s;
  ray *r;
  point *p;

  bool operator==(const ray *in_ray) const { return is_ray && in_ray == r; }

  bool operator<(const event &another) const {
    if(p->y > another.p->y) return true;
    if(another.p->y > p->y) return false;
    if(type != another.type) {
      if(type == types::end) return true;
      return false;
    }
    if(abs(p->x - another.p->x) < 0.0001) return is_ray;
    return p->x < another.p->x;
  }
};


class scan_line {
public:
  scan_line(double y) : y(y) {}
  double y;
  bool operator()(const segment &left_s, const segment &right_s) const {
    return left_s.x_from_y(y) < right_s.x_from_y(y);
  }
  bool operator()(const ray &left_r, const ray &right_r) const {
    if(abs(left_r.start->x - right_r.start->x) > 0.1)
      return left_r.start->x < right_r.start->x;
    return left_r.start->y > right_r.start->y;
  }
  bool operator()(const ray &r, const segment &s) const {
    double sx = s.x_from_y(y);
    if(abs(r.start->x - sx) < 0.001) return false;
    return r.start->x < sx;
  }
  bool operator()(const segment &s, const ray &r) const {
    double sx = s.x_from_y(y);
    if(abs(r.start->x - sx) < 0.001) return true;
    return sx < r.start->x;
  }
  bool operator()(const adapter &a, const segment &s) const {
    if(a.is_ray) return this->operator()(*a.r, s);
    return this->operator()(*a.s, s);
  }
  bool operator()(const adapter &a, const ray &r) const {
    if(a.is_ray) return this->operator()(*a.r, r);
    return this->operator()(*a.s, r);
  }
  bool operator()(const segment &s, const adapter &a) const {
    if(a.is_ray) return this->operator()(s, *a.r);
    return this->operator()(s, *a.s);
  }
  bool operator()(const ray &r, const adapter &a) const {
    if(a.is_ray) return this->operator()(r, *a.r);
    return this->operator()(r, *a.s);
  }
};

std::ostream& operator<<(std::ostream &out, const adapter &in_adapter) {
  if(in_adapter.is_ray) out << "AR " << *in_adapter.r;
  else out << "AS " << *in_adapter.s;
  return out;
}

std::ostream& operator<<(std::ostream &out, const event &in_event) {
  out << (in_event.type == event::types::start ? "start" : "end") << " ";
  if(in_event.is_ray) {
    out << "ray " << *in_event.r << " with point " << *in_event.p;
  } else {
    out << "line " << *in_event.s << " from " << *in_event.p;
  }
  return out;
}

std::vector<intersection> find_intersections(std::vector<segment*> &lines, std::vector<ray*> &rays) {
  std::vector<event> events;
  events.reserve(2 * lines.size() + rays.size());
  for(segment *line : lines) {
    events.push_back(event(event::types::start, line, line->start));
    events.push_back(event(event::types::end, line, line->end));
  }
  for(ray *r : rays) events.push_back(event(r));
  std::sort(events.begin(), events.end());
#ifdef ALGO_DEBUG
  std::copy(events.begin(), events.end(), std::ostream_iterator<event>(std::cerr, "\n"));
#endif
  std::vector<adapter> adapters;
  std::vector<intersection> intersections;
  std::set<event> ray_events;
  auto event_it = events.begin();
#ifdef ALGO_DEBUG
  std::cerr << std::setprecision(2);
#endif
  while(event_it != events.end()) {
#ifdef ALGO_DEBUG
    if(!ray_events.empty()) {
      TRACE_LINE("compare event " << *event_it << " to ray killer " << *ray_events.begin());
    }
#endif
    if(!ray_events.empty() && *ray_events.begin() < *event_it) {
      event ev = *ray_events.begin(); ray_events.erase(ray_events.begin());
      ASSERT(ev.is_ray);
      intersections.push_back(intersection(ev.r));
      TRACE_LINE("looking for " << *ev.r);
      scan_line level(ev.r->start->y == ev.p->y ? ev.r->start->y : ev.p->y + 0.00001);
      auto pos = std::lower_bound(adapters.begin(), adapters.end(), *ev.r, level);
      ASSERT(pos != adapters.end());
      ASSERT(pos->r == ev.r);
      TRACE_LINE("remove ray " << *pos);
      if((pos + 1) != adapters.end() && pos != adapters.begin()) {
        adapter left = *(pos - 1);
        adapter right = *(pos + 1);
        TRACE_LINE("check " << left << " and " << right);
        if(left.intersects(right)) {
          TRACE_LINE("intersection: " << left << " and " << right);
          if(left.is_ray) {
            left.r->intersected_segment = right.s;
            if(left.r->intersection != nullptr) {
              TRACE_LINE("delete ray killer " << *left.r << " at " << *left.r->intersection);
              ray_events.erase(std::find(ray_events.begin(), ray_events.end(),left.r));
              delete left.r->intersection;
            }
            left.r->intersection = new point(left.r->start->x, right.s->y_from_x(left.r->start->x));
            ASSERT(left.r->intersection->y <= ev.p->y);
            TRACE_LINE("add ray killer " << *left.r << " at " << *left.r->intersection);
            ray_events.emplace(event::types::end, left.r, left.r->intersection);
          } else {
            right.r->intersected_segment = left.s;
            if(right.r->intersection != nullptr) {
              TRACE_LINE("delete ray killer " << *right.r << " at " << *right.r->intersection);
              ray_events.erase(std::find(ray_events.begin(), ray_events.end(),right.r));
              delete right.r->intersection;
            }
            right.r->intersection = new point(right.r->start->x, left.s->y_from_x(right.r->start->x));
            ASSERT(right.r->intersection->y <= ev.p->y);
            TRACE_LINE("add ray killer " << *right.r << " at " << *right.r->intersection);
            ray_events.emplace(event::types::end, right.r, right.r->intersection);
          }
        }
      }
      adapters.erase(pos);
    } else {
      event ev = *(event_it++);
      if(ev.type == event::types::start) {
        if(ev.is_ray) {
          auto pos = std::upper_bound(adapters.begin(), adapters.end(), *ev.r, scan_line(ev.p->y));
#ifdef ALGO_DEBUG
          if(pos != adapters.end())
            std::cerr << "add " << *ev.r << " before " << *pos << std::endl;
          else std::cerr << "add " << *ev.r << " in the end" << std::endl;
#endif
          if(pos != adapters.begin()) {
            TRACE_LINE("check " << *(pos - 1) << " and " << *ev.r);
            if((pos - 1)->intersects(*ev.r)) {
              ASSERT(!(pos - 1)->is_ray);
              TRACE_LINE("intersection(-1): " << *ev.r << " and " << *(pos - 1));
              segment *intersector = (pos - 1)->s;
              ev.r->intersected_segment = intersector;
              ev.r->intersection = new point(ev.r->start->x, intersector->y_from_x(ev.r->start->x));
              ASSERT(ev.r->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *ev.r << " at " << *ev.r->intersection);
              ray_events.emplace(event::types::end, ev.r, ev.r->intersection);
            }
          }
          if(pos != adapters.end()) {
            TRACE_LINE("check " << *pos << " and " << *ev.r);
            if(pos->intersects(*ev.r)) {
              ASSERT(!pos->is_ray);
              TRACE_LINE("intersection(+1): " << *ev.r << " and " << *pos);
              segment *intersector = pos->s;
              if(ev.r->intersection != nullptr) {
                TRACE_LINE("delete ray killer " << *ev.r << " at " << *ev.r->intersection);
                ray_events.erase(std::find(ray_events.begin(), ray_events.end(),ev.r));
                delete ev.r->intersection;
              }
              ev.r->intersected_segment = intersector;
              ev.r->intersection = new point(ev.r->start->x, intersector->y_from_x(ev.r->start->x));
              ASSERT(ev.r->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *ev.r << " at " << *ev.r->intersection);
              ray_events.emplace(event::types::end, ev.r, ev.r->intersection);
            }
          }
          adapters.insert(pos, adapter(ev.r));
        } else {
          auto pos = std::upper_bound(adapters.begin(), adapters.end(), *ev.s, scan_line(ev.p->y));
#ifdef ALGO_DEBUG
          if(pos != adapters.end()) std::cerr << "add " << *ev.s << " before " << *pos << std::endl;
          else std::cerr << "add " << *ev.s << " in the end" << std::endl;
#endif
          if(pos != adapters.begin()) {
            TRACE_LINE("check: " << *ev.s << " and " << *(pos - 1));
            if((pos - 1)->intersects(*ev.s)) {
              ASSERT((pos - 1)->is_ray);
              TRACE_LINE("intersection (-1): " << *ev.s << " and " << *(pos - 1));
              ray *intersected = (pos - 1)->r;
              intersected->intersected_segment = ev.s;
              if(intersected->intersection != nullptr) {
                TRACE_LINE("delete ray killer " << *intersected << " at " << *intersected->intersection);
                ray_events.erase(std::find(ray_events.begin(), ray_events.end(),intersected));
                delete intersected->intersection;
              }
              intersected->intersection =
                new point(intersected->start->x, ev.s->y_from_x(intersected->start->x));
              ASSERT(intersected->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *intersected << " at " << *intersected->intersection);
              ray_events.emplace(event::types::end, intersected, intersected->intersection);
            }
          }
          if(pos != adapters.end()) {
            TRACE_LINE("check: " << *ev.s << " and " << *pos);
            if(pos->intersects(*ev.s)) {
              ASSERT(pos->is_ray);
              TRACE_LINE("intersection (+1): " << *ev.s << " and " << *pos);
              ray *intersected = pos->r;
              intersected->intersected_segment = ev.s;
              if(intersected->intersection != nullptr) {
                TRACE_LINE("delete ray killer " << *intersected << " at " << *intersected->intersection);
                ray_events.erase(std::find(ray_events.begin(), ray_events.end(),intersected));
                delete intersected->intersection;
              }
              intersected->intersection =
                new point(intersected->start->x, ev.s->y_from_x(intersected->start->x));
              ASSERT(intersected->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *intersected << " at " << *intersected->intersection);
              ray_events.emplace(event::types::end, intersected, intersected->intersection);
            }
          }
          adapters.insert(pos, adapter(ev.s));
        }
      } else {
        auto pos = std::lower_bound(adapters.begin(), adapters.end(), *ev.s, scan_line(ev.p->y));
        ASSERT(pos != adapters.end());
        TRACE_LINE("remove " << *pos);
        if((pos + 1) != adapters.end() && pos != adapters.begin()) {
          adapter left = *(pos - 1);
          adapter right = *(pos + 1);
          TRACE_LINE("check " << left << " and " << right);
          if(left.intersects(right)) {
            TRACE_LINE("intersection: " << left << " and " << right);
            if(left.is_ray) {
              right.r->intersected_segment = left.s;
              if(right.r->intersection != nullptr) {
                TRACE_LINE("delete ray killer " << *right.r << " at " << *right.r->intersection);
                ray_events.erase(std::find(ray_events.begin(), ray_events.end(),right.r));
                delete right.r->intersection;
              }
              right.r->intersection = new point(right.r->start->x, left.s->y_from_x(right.r->start->x));
              ASSERT(right.r->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *right.r << " at " << *right.r->intersection);
              ray_events.emplace(event::types::end, right.r, right.r->intersection);
            } else {
              left.r->intersected_segment = right.s;
              if(left.r->intersection != nullptr) {
                TRACE_LINE("delete ray killer " << *left.r << " at " << *left.r->intersection);
                ray_events.erase(std::find(ray_events.begin(), ray_events.end(),left.r));
                delete left.r->intersection;
              }
              left.r->intersection = new point(left.r->start->x, right.s->y_from_x(left.r->start->x));
              ASSERT(left.r->intersection->y <= ev.p->y);
              TRACE_LINE("add ray killer " << *left.r << " at " << *left.r->intersection);
              ray_events.emplace(event::types::end, left.r, left.r->intersection);
            }
          }
        }
        adapters.erase(pos);
      }
    }
#ifdef ALGO_DEBUG
    std::copy(adapters.begin(), adapters.end(), std::ostream_iterator<adapter>(std::cerr, "; "));
    std::cerr << std::endl;
#endif
  }
  return intersections;
}

void unit_tests() {
}

int main() {
  UNIT_TESTS();
  int N, Q;
  std::cin >> N >> Q;
  std::vector<segment*> lines;
  std::vector<ray*> rays;
  for(int i = 0; i < N; ++i) {
    segment *line = new segment;
    std::cin >> *line;
    lines.push_back(line);
    ray *downward = new ray(line);
    rays.push_back(downward);
  }
#ifdef ALGO_DEBUG
  std::cerr << "-- building segment tree" << std::endl;
#endif
  std::vector<intersection> intersections = find_intersections(lines, rays);
  auto tree_it = intersections.rbegin();
  while(tree_it != intersections.rend()) {
    tree_it->who->owning_segment->drop_x = tree_it->where->drop_x;
    ++tree_it;
  }
  rays.clear();
  for(int i = 0; i < Q; ++i) {
    ray *ball = new ray;
    ball->start = new point;
    std::cin >> *ball->start;
    rays.push_back(ball);
  }
#ifdef ALGO_DEBUG
  std::cerr << "-- droping balls" << std::endl;
#endif
  intersections = find_intersections(lines, rays);
  // tree_it = intersections.rbegin();
  // while(tree_it != intersections.rend()) {
  //   tree_it->who->drop_x = tree_it->where->drop_x;
  //   ++tree_it;
  // }
  for(ray* r : rays) {
    if(r->intersection == nullptr)
      std::cout << r->start->x << std::endl;
    else
      std::cout << r->intersected_segment->drop_x << std::endl;
  }
  return 0;
}
