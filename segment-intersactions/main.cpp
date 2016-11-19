#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else

#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)

#endif

class point {
public:
  explicit point() {}
  point(int x, int y): x(x), y(y) {}
  int x, y;
};

std::istream& operator>>(std::istream& in, point &out_point) {
  in >> out_point.x >> out_point.y;
  return in;
}

std::ostream& operator<<(std::ostream& out, const point &in_point) {
  out << in_point.x << " " << in_point.y;
  return out;
}

class segment {
public:
  explicit segment() {}
  segment(point *start, point *end): start(start), end(end) {}
  segment(int start_x, int start_y, int end_x, int end_y) {
    create_points();
    start->x = start_x; start->y = start_y;
    end->x = end_x; end->y = end_y;
  }
  point *start, *end;
  void create_points() {
    start = new point;
    end = new point;
  }
};

class segment_wrapper : public segment {
public:
  segment_wrapper(point *start, point *end, segment *original)
    :segment(start, end)
    ,original(original) {
  }
  segment *original;
};

std::istream& operator>>(std::istream& in, segment &out_segment) {
  in >> *out_segment.start >> *out_segment.end;
  return in;
}

std::ostream& operator<<(std::ostream& out, const segment &in_segment) {
  out << *in_segment.start << " " << *in_segment.end;
  return out;
}

class intersection {
public:
  intersection(segment *one, segment *two):one(one), two(two) {}
  segment *one, *two;
  point *where;
};

class event {
public:
  enum class types {
    start, end
  };
  event(segment *in_line, types in_type, point *in_where)
    :line(in_line)
    ,type(in_type)
    ,where(in_where) {
  }

  segment *line;
  types type;
  point *where;
};

bool operator<(const event &left, const event &right) {
  if(left.where->x < right.where->x) return true;
  if(left.where->x > right.where->x) return false;
  if(left.type != right.type) {
    if(left.type == event::types::end) return true;
    return false;
  }
  return left.where->y < right.where->y;
}

std::ostream& operator<<(std::ostream& out, const event::types &in_type) {
  out << (in_type == event::types::start ? "start" : "end");
  return out;
}

std::ostream& operator<<(std::ostream& out, const event &in_event) {
  out << in_event.type << " " << *in_event.line << " at " << *in_event.where;
  return out;
}

std::ostream& operator<<(std::ostream& out, const intersection &in_intersection) {
  out << *in_intersection.one << "\n" << *in_intersection.two;
  return out;
}

point operator-(const point &left, const point &right) { return point(left.x - right.x, left.y - right.y); }

int dot(const point &root, const point &from, const point &to) {
  point norm_from = from - root, // 0 1 vertical up
    norm_to = to - root; // 1 0 horizontal right
  // 0 * 0 < 1 * 1 - clockwise
  return norm_from.x * norm_to.y - norm_from.y * norm_to.x;
}

bool is_clockwise(const point &root, const point &from, const point &to) {
  return dot(root, from, to) < 0;
}

inline point* left_point(const segment &line) { return line.start->x > line.end->x ? line.end : line.start; }
inline point* right_point(const segment &line) { return line.start->x < line.end->x ? line.end : line.start; }

bool is_point_p_above_segment_p(const point *in_point, const segment *line) {
  return is_clockwise(*left_point(*line), *in_point, *right_point(*line));
}

bool between(const point &one, const point &two, const point &target) {
  return target.x <= std::max(one.x, two.x) && target.x >= std::min(one.x, two.x) &&
    target.y <= std::max(one.y, two.y) && target.y >= std::min(one.y, two.y);
}

bool intersect(const segment &one, const segment &two) {
  int d0 = dot(*one.start, *one.end, *two.start),
    d1 = dot(*one.start, *one.end, *two.end),
    d2 = dot(*two.start, *two.end, *one.start),
    d3 = dot(*two.start, *two.end, *one.end);
  if(((d0 > 0 && d1 < 0) || (d0 < 0 && d1 > 0)) &&
     ((d2 > 0 && d3 < 0) || (d2 < 0 && d3 > 0))) return true;
  if(d0 == 0 && between(*one.start, *one.end, *two.start)) return true;
  if(d1 == 0 && between(*one.start, *one.end, *two.end)) return true;
  if(d2 == 0 && between(*two.start, *two.end, *one.start)) return true;
  if(d3 == 0 && between(*two.start, *two.end, *one.end)) return true;
  return false;
}

std::vector<intersection> search_intersections(std::vector<segment*> &lines) {
  std::vector<event> events;
  for(segment* line : lines) {
    if(line->start->x < line->end->x) {
      events.push_back(event(line, event::types::start, line->start));
      events.push_back(event(line, event::types::end, line->end));
    } else {
      events.push_back(event(line, event::types::start, line->end));
      events.push_back(event(line, event::types::end, line->start));
    }
  }
  std::sort(events.begin(), events.end());
  //std::copy(events.begin(), events.end(), std::ostream_iterator<event>(std::cout, "\n"));
  std::vector<intersection> intersections;
  std::vector<segment*> sweep_line;
  for(event &ev : events) {
    if(ev.type == event::types::start) {
      std::vector<segment*>::iterator first_above =
        std::upper_bound(sweep_line.begin(), sweep_line.end(), ev.where, is_point_p_above_segment_p);
      // std::cout  << "add " << *ev.line;
      // if(first_above == sweep_line.end()) std::cout << " in the end" << std::endl;
      // else std::cout << " before " << **first_above << std::endl;
      bool is_intersected = false;
      if(first_above != sweep_line.end()) {
        if(intersect(**first_above, *ev.line)) {
          is_intersected = true;
          intersections.push_back(intersection(*first_above, ev.line));
          // std::cout << **first_above << " intersects " << *ev.line << std::endl;
        }
      }
      if(first_above != sweep_line.begin()) {
        if(intersect(**(first_above - 1), *ev.line)) {
          is_intersected = true;
          intersections.push_back(intersection(*(first_above - 1), ev.line));
          // std::cout << **(first_above - 1) << " intersects " << *ev.line << std::endl;
        }
      }
      if(!is_intersected)
        sweep_line.insert(first_above, ev.line);
    } else {
      std::vector<segment*>::iterator pos_in_sweep = std::find(sweep_line.begin(), sweep_line.end(), ev.line);
      // std::cout << "removing " << **pos_in_sweep;
      if(pos_in_sweep != sweep_line.begin() && pos_in_sweep != sweep_line.end()) {
        std::vector<segment*>::iterator above = pos_in_sweep - 1, below = pos_in_sweep + 1;
        while(below != sweep_line.end() && intersect(**above, **below)) {
]          // std::cout << **above << " intersects " << **below;
          intersections.push_back(intersection(*above, *below));
          sweep_line.erase(below);
        }
      }
      // if(pos_in_sweep == sweep_line.end()) std::cout << " NOT FOUND!";
      if(pos_in_sweep != sweep_line.end()) sweep_line.erase(pos_in_sweep);
      // std::cout << std::endl;
    }
  }
  return intersections;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<segment*> lines;
  for(int i = 0; i < N; ++i) {
    segment* line = new segment;
    line->create_points();
    std::cin >> *line;
    lines.push_back(line);
  }
  std::vector<intersection> intersections = search_intersections(lines);
  std::copy(intersections.begin(), intersections.end(), std::ostream_iterator<intersection>(std::cout, "\n"));
  return 0;
}
