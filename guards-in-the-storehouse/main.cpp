#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <string>
#include <sstream>

#define fr(v,s,e) for(int v = s; v < e; ++v)
#define fl(v,s,e) for(int v = s; v > e; --v)

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

constexpr long long mod = 1e9 + 7;

class mat {
  std::vector<bool> _data;
  int _rows, _cols;
 public:
  mat(int rows, int cols) : _rows{rows}, _cols{cols} {
    _data.resize(_rows * _cols);
  }
  mat(const mat &other) : _rows{other._rows}, _cols{other._cols},
                          _data{other._data}
  {
  }
  mat(mat &&other) : _rows{other._rows}, _cols{other._cols},
                     _data{std::move(other._data)}
  {
  }

  inline bool is_wall(int r, int c) const { return _data[r * _cols + c]; }
  inline void set_wall(int r, int c, bool wall) { _data[r * _cols + c] = wall; }

  inline int size() const { return _rows * _cols; }

  inline int rows() const { return _rows; }
  inline int cols() const { return _cols; }

  mat t() {
    mat res(_cols, _rows);
    fr(r,0,_rows) fr(c,0,_cols) res.set_wall(c, r, is_wall(r, c));
    return res;
  }

  mat& operator=(const mat &other) {
    _rows = other._rows;
    _cols = other._cols;
    _data = other._data;
    return *this;
  }

  std::string
  to_debug_string(std::string cols_delim, std::string rows_delim) const {
    std::stringstream out;
    fr(r,0,_rows) {
      if(r > 0) out << rows_delim;
      fr(c,0,_cols) {
        if(c > 0) out << cols_delim;
        out << (is_wall(r, c) ? 'x' : '.');
      }
    }
    return out.str();
  }
};

struct combination {
  int mask; // which rows are protected
  bool is_column_protected; // if column is protected
  int count_not_protected; // number of cells we did not protect
};

bool operator<(const combination& left, const combination& right) {
  if(left.is_column_protected != right.is_column_protected)
    return left.is_column_protected;
  if(left.count_not_protected != right.count_not_protected)
    return left.count_not_protected < right.count_not_protected;
  return left.mask < right.mask;
}

bool operator==(const combination& left, const combination& right) {
  return left.is_column_protected == right.is_column_protected &&
      left.count_not_protected == right.count_not_protected &&
      left.mask == right.mask;
}

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
  int rows, cols;
  std::cin >> rows >> cols;
  mat storehouse(rows, cols);
  fr(r,0,rows) {
    char line[251];
    std::cin >> line;
    fr(c,0,cols) {
      storehouse.set_wall(r, c, line[c] == 'x');
    }
  }
  TRACE_LINE("read was fine");
  if(cols > 15) {
    storehouse = storehouse.t();
    TRACE_LINE(storehouse.to_debug_string("", "\n"));
  }
  std::map<combination, long long> histo;
  histo[{0, false, 1}] = 1ll;
  fr(r,0,storehouse.rows()) {
    TRACE_LINE("- " << r << " " << histo.size());
    int col_mask = 1;
    std::map<combination, long long> next_histo;
    for(auto& pair : histo) {
      combination comb = pair.first;
      assert(comb.mask >= 0);
      assert(comb.mask < (1 << storehouse.cols()));
      long long count = pair.second;
      if(!comb.is_column_protected) {
        next_histo[comb] = (next_histo[comb] + count) % mod;
        continue;
      }
      combination next_comb;
      next_comb.mask = comb.mask;
      next_comb.is_column_protected = false;
      next_comb.count_not_protected = comb.count_not_protected;
      next_histo[next_comb] = (next_histo[next_comb] + count) % mod;
    }
    histo = std::move(next_histo);
    fr(c,0,storehouse.cols()) {
      next_histo.clear();
      if(storehouse.is_wall(r, c)) {
        for(auto& pair : histo) {
          combination comb = pair.first;
          long long count = pair.second;
          combination next_comb;
          next_comb.mask = comb.mask & ~col_mask;
          next_comb.is_column_protected = false;
          next_comb.count_not_protected = comb.count_not_protected;
          next_histo[next_comb] = (next_histo[next_comb] + count) % mod;
        }
      } else {
        for(auto& pair : histo) {
          combination comb = pair.first;
          long long count = pair.second;
          combination next_comb;
          // we do not place guard
          if(comb.is_column_protected || (comb.mask & col_mask)) {
            // column is protected, or row is protected
            // we may not put guard here
            next_comb.mask = comb.mask;
            next_comb.is_column_protected = comb.is_column_protected;
            next_comb.count_not_protected = comb.count_not_protected;
            next_histo[next_comb] = (next_histo[next_comb] + count) % mod;
          } else if(comb.count_not_protected > 0) {
            // neither column, nor row is protected
            // by not putting guard here - we increse not protected cells
            next_comb.mask = comb.mask;
            next_comb.is_column_protected = comb.is_column_protected; // false
            next_comb.count_not_protected = comb.count_not_protected - 1;
            next_histo[next_comb] = (next_histo[next_comb] + count) % mod;
          }
          // we place guard
          next_comb.mask = comb.mask | col_mask;
          next_comb.is_column_protected = true;
          next_comb.count_not_protected = comb.count_not_protected;
          next_histo[next_comb] = (next_histo[next_comb] + count) % mod;
        }
      }
      histo = std::move(next_histo);
      col_mask <<= 1;
    }
  }
  long long total = 0;
  for(auto& pair : histo) {
    total = (total + pair.second) % mod;
  }
  std::cout << total << std::endl;
  return 0;
}
