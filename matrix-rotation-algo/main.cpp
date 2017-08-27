#include <iostream>
#include <vector>

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

struct pos {
  int r, c;
};

class mat {
  int *_vals;
  int _cols, _rows;
  bool _owner;
 public:
  mat(int rows, int cols) : _owner{true}, _rows{rows},
    _cols{cols}, _vals{new int[cols * rows]} {}
  mat(int rows, int cols, int *vals) : _owner{false}, _rows{rows},
    _cols{cols}, _vals{vals} {}
  mat(const mat& other) = delete;
  mat(mat&& other) : _owner{other._owner}, _rows{other._rows},
    _cols{other._cols}, _vals{other._vals}
  {
    other._owner = false;
  }
  ~mat() {
    if(_owner) delete[] _vals;
  }

  inline int cols() const { return _cols; }
  inline int rows() const { return _rows; }

  inline int& at(int r, int c) { return _vals[r * _cols + c]; }
  inline const int& at(int r, int c) const { return _vals[r * _cols + c]; }

  mat L() const {
    mat other(_cols, _rows);
    fr(r,0,_rows) fr(c,0,_cols) other.at(c, _rows - r - 1) = at(r,c);
    return other;
  }

  mat R() const {
    mat other(_cols, _rows);
    fr(r,0,_rows) fr(c,0,_cols) other.at(_cols - c - 1, r) = at(r,c);
    return other;
  }
};

std::vector<pos> walk(const int &rows, const int &cols, const int &drows,
                      const int &dcols) {
  std::vector<pos> res;
  res.reserve(2 * (rows + cols - 2));
  fr(r,0,rows) res.push_back({r + drows, dcols});
  fr(c,1,cols) res.push_back({rows + drows - 1, c + dcols});
  fl(r,rows-2,-1) res.push_back({r + drows, cols + dcols - 1});
  fl(c,cols-2,0) res.push_back({drows, c + dcols});
  return res;
}

mat rotate(const mat &A, int rots) {
  mat B(A.rows(), A.cols());
  fr(d,0,A.rows()/2) {
    if(A.cols() - 2 * d <= 1) break;
    std::vector<pos> iter = walk(A.rows() - 2 * d, A.cols() - 2 * d, d, d);
    int steps = iter.size();
    for(int step = 0;  step < steps; ++step) {
      const pos &from = iter[step];
      const pos &to = iter[(step + rots) % steps];
      B.at(to.r, to.c) = A.at(from.r, from.c);
    }
  }
  return B;
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
  int rows, cols, rots;
  std::cin >> rows >> cols >> rots;
  mat A(rows, cols);
  fr(r,0,rows) {
    fr(c,0,cols) {
      std::cin >> A.at(r, c);
    }
  }
  mat B = rows % 2 == 0 ? rotate(A, rots) : rotate(A.L(), rots).R();
  fr(r,0,rows) {
    fr(c,0,cols) {
      if(c > 0) std::cout << " ";
      std::cout << B.at(r,c);
    }
    std::cout << "\n";
  }
  return 0;
}
