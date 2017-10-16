#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define fr(v,s,e) for(long long v = s; v < e; ++v)
#define fl(v,s,e) for(long long v = s; v > e; --v)

#ifdef UNITS
#include "../test/units.cpp"
#endif

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

struct triple {
  long long number, other, sum;
};

bool by_number(const triple &left, const triple &right) {
  return left.number < right.number;
}

bool by_other(const triple &left, const triple &right) {
  return left.other < right.other;
}

class tree {
public:
  tree(long long N) : N{N} {
    d = 1, size = 1;
    while(size < N) {
      ++d;
      size <<= 1;
    }
    values.resize(size << 1);
    bounds.resize(size << 1);
    cache.resize(size << 1);
  }
  void set_bound(long long ind, long long bound, long long value) {
    assert(ind < size);
    bounds[size + ind] = std::make_pair(bound, bound);
    values[size + ind] = value;
  }
  void build(long long start, long long mult) {
    std::fill(cache.begin(), cache.end(), 0);
    fr(i,0,size) {
      values[size + i] += std::abs(bounds[size + i].first - start) * mult;
    }
    fl(i,size-1,0) {
      long long l = i<<1, r = l + 1;
      if(l >= size + N) {
        bounds[l] = std::make_pair(-1,-1);
        continue;
      }
      if(r >= size + N) {
        bounds[i] = bounds[l];
        values[i] = values[l];
      } else {
        bounds[i] = std::make_pair(bounds[l].first, bounds[r].second);
        values[i] = std::max(values[l], values[r]);
      }
    }
  }
  long long max() { push(1); return values[1]; }
  void modify(long long node, long long before, long long after, long long mul) {
    if(bounds[node].first == -1) return;
    if(cache[node] > 0) push(node);
    long long diff = (after - before) * mul;
    if(bounds[node].second <= before) {
      cache[node] += diff;
    } else if(bounds[node].first >= after) {
      cache[node] -= diff;
    } else {
      if(node >= size) {
        long long bound = bounds[node].first;
        long long diff = (std::abs(bound - after) - std::abs(bound - before)) * mul;
        values[node] += diff;
      } else {
        long long left = node << 1, right = left + 1;
        modify(left, before, after, mul);
        push(left);
        if(bounds[right].first != -1) {
          modify(right, before, after, mul);
          push(right);
          values[node] = std::max(values[left], values[right]);
        } else {
          values[node] = values[left];
        }
      }
    }
  }
  void push(long long node) {
    if(node >= size) return;
    long long left = 2 * node, right = left + 1;
    if(left < size) {
      cache[left] += cache[node];
      cache[right] += cache[node];
    } else {
      if(left - size < N) {
        values[left] += cache[node];
        if(right - size < N) {
          values[right] += cache[node];
        }
      }
    }
    values[node] +=cache[node];
    cache[node] = 0;
  }
  tree& operator=(tree &&other) {
    size = other.size; d = other.d; N = other.N;
    values = std::move(other.values);
    cache = std::move(other.cache);
    bounds = std::move(other.bounds);
    return *this;
  }
  long long size, d, N;
  std::vector<long long> values, cache;
  std::vector<std::pair<long long, long long>> bounds;
};

#ifdef UNITS
void unit_tests() {
  test_header("test units");
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  long long T;
  std::cin >> T;
  while(T--) {
    long long N;
    std::cin >> N;
    long long s;
    std::cin >> s;
    std::vector<long long> V(s);
    fr(i,0,s) {
      std::cin >> V[i];
    }
    std::sort(V.begin(), V.end());
    tree t(s);
    fr(i,0,s) t.set_bound(i, V[i], 0);
    fr(i,1,N) {
      TRACE_LINE("== " << i);
      std::cin >> s;
      std::vector<triple> V(s);
      fr(j,0,s) {
        std::cin >> V[j].number;
        if(j > 0) V[j].other = V[j-1].number;
      }
      V[0].other = V[s-1].number;
      std::sort(V.begin(), V.end(), by_number);
      t.build(V[0].number, i);
      V[0].sum = t.max();
      TRACE_LINE(V[0].number << " -> " << V[0].other << ": " << V[0].sum);
      fr(j,1,s) {
        t.modify(1, V[j-1].number, V[j].number, i);
        V[j].sum = t.max();
        TRACE_LINE(V[j].number << " -> " << V[j].other << ": " << V[j].sum);
      }
      if(i == N-1) {
        long long res = 0;
        for(const auto &p : V) {
          res = std::max(p.sum, res);
        }
        std::cout << res << "\n";
        break;
      }
      std::sort(V.begin(), V.end(), by_other);
      tree t2(s);
      fr(j,0,s) {
        t2.set_bound(j, V[j].other, V[j].sum);
      }
      t = std::move(t2);
    }
  }
  return 0;
}
