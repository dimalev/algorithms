#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>

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

template<class T>
class Mat {
  T *data;
  const int _rows, _cols;
 public:
  Mat(int _rows, int _cols)
      : _rows{_rows}, _cols{_cols}, data{new T[_rows * _cols]}
  {
    std::fill(data, data + size(), 0);
  }

  Mat(const Mat &other)
      : _rows{other._rows}, _cols{other._cols}, data{new T[_rows * _cols]}
  {
    std::copy_n(other.data, data, size());
  }

  Mat(Mat &&other)
      : _rows{other._rows}, _cols{other._cols}, data{other.data}
  {
    data = other.data;
    other.data = nullptr;
  }

  virtual ~Mat() {
    if(data != nullptr) {
      delete[] data;
    }
  }

  inline int size() const { return _rows * _cols; }
  inline int rows() const { return _rows; }
  inline int cols() const { return _cols; }

  inline int pos(int r, int c) const { return r * _cols + c; }

  T at(int p) const {
    assert(p < size() && p >= 0);
    return data[p];
  }

  T& at(int p) {
    assert(p < size() && p >= 0);
    return data[p];
  }

  T at(int r, int c) const {
    assert(r < _rows && r >= 0);
    assert(c < _cols && c >= 0);
    return data[pos(r, c)];
  }

  T& at(int r, int c) {
    assert(r < _rows && r >= 0);
    assert(c < _cols && c >= 0);
    return data[pos(r, c)];
  }

  Mat operator*(const Mat &right) const {
    if(_cols != right._rows) throw "Size mismatch";
    Mat result{_rows, right._cols};
    for(int i = 0; i < _rows; ++i) {
      for(int j = 0; j < right._cols; ++j) {
        result.at(i, j) = 0;
        for(int k = 0; k < _cols; ++k) {
          result.at(i, j) += at(i, k) * right.at(k, j);
        }
      }
    }
    return result;
  }

  Mat& operator=(const Mat &right) {
    if(_cols != right._cols || _rows != right._rows) throw "Size mismatch";
    std::copy_n(right.data, data, size());
    return *this;
  }

  Mat& operator=(Mat &&right) {
    delete[] data;
    data = right.data;
    right.data = nullptr;
    return *this;
  }

  Mat reshape(int new_rows, int new_cols) {
    if(new_rows * new_cols != size()) throw "Size mismatch";
    Mat res{new_rows, new_cols};
    for(int i = 0; i < size(); ++i) {
      res.at(i) = at(i);
    }
    return res;
  }

  Mat row(int r) {
    Mat res{1, _cols};
    for(int i = 0; i < _cols; ++i) {
      res.at(i) = at(r, i);
    }
  }

  Mat col(int c) {
    Mat res{_rows, 1};
    for(int i = 0; i < _rows; ++i) {
      res.at(i) = at(i, c);
    }
  }

  Mat t() const {
    Mat res{_cols, _rows};
    for(int r = 0; r < _rows; ++r) {
      for(int c = 0; c < _cols; ++c) {
        res.at(c, r) = at(r, c);
      }
    }
    return res;
  }
};

template<typename T>
std::istream& operator>>(std::istream& in, Mat<T> &res) {
  for(int i = 0; i < res.size(); ++i) {
    in >> res.at(i);
  }
  return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Mat<T> &res) {
  for(int r = 0; r < res.rows(); ++r) {
    for(int c = 0; c < res.cols(); ++c) {
      if(c > 0) out << "\t";
      out << res.at(r, c);
    }
    out << std::endl;
  }
  return out;
}

#ifdef UNITS
void unit_tests() {
  test_header("matrix input");
  int rows, cols;
  std::cin >> rows >> cols;
  Mat<int> res{rows, cols};
  std::cin >> res;
  std::cout << res;
  test_header("matrix multiply");
  std::cin >> rows >> cols;
  Mat<int> left{rows, cols};
  std::cin >> left;
  std::cin >> rows >> cols;
  Mat<int> right{rows, cols};
  std::cin >> right;
  std::cout << (left * right);
}
#endif

int main() {
#ifdef UNITS
  unit_tests();
  return 0;
#endif
  int rows, cols, pipes_count;
  std::cin >> rows >> cols >> pipes_count;
  std::cin.ignore();
  Mat<int> start{1, 2};
  Mat<bool> obstacles{rows, cols}, bombs{rows, cols};
  Mat<float> ends{rows, cols};
  Mat<int> pipes{pipes_count, 4};
  for(int r = 0; r < rows; ++r) {
    char line[21];
    std::cin.getline(line, cols + 1);
    for(int c = 0; c < cols; ++c) {
      switch(line[c]) {
        case '#':
          obstacles.at(r, c) = true;
          break;
        case '*':
          bombs.at(r, c) = true;
          break;
        case 'A':
          start.at(0) = r;
          start.at(1) = c;
          break;
        case '%':
          ends.at(r, c) = 1.0;
          bombs.at(r, c) = true;
          break;
      }
    }
  }
  std::cin >> pipes;
  for(int i = 0; i < pipes_count; ++i) {
    // for all pipe bottoms - we treat it like bomb - no way OUT of it
    bombs.at(pipes.at(i, 0) - 1, pipes.at(i, 1) - 1) = true;
  }
  Mat<int> paths{rows, cols};
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      if(obstacles.at(r, c)) continue;
      if(r > 0 && !obstacles.at(r - 1, c))
        ++paths.at(r - 1, c);
      if(r < rows - 1 && !obstacles.at(r + 1, c))
        ++paths.at(r + 1, c);
      if(c > 0 && !obstacles.at(r, c - 1))
        ++paths.at(r, c - 1);
      if(c < cols - 1 && !obstacles.at(r, c + 1))
        ++paths.at(r, c + 1);
    }
  }

  // std::cout << paths << std::endl;

  Mat<float> current{rows * cols, 1};
  Mat<float> move{rows * cols, rows * cols};
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      if(obstacles.at(r, c)) continue;
      int p = ends.pos(r, c);
      if(r > 0 && !obstacles.at(r - 1, c) && ! bombs.at(r - 1, c))
        move.at(p, ends.pos(r - 1, c)) = 1.0 / paths.at(r - 1, c);
      if(r < rows - 1 && !obstacles.at(r + 1, c) && !bombs.at(r + 1, c))
        move.at(p, ends.pos(r + 1, c)) = 1.0 / paths.at(r + 1, c);
      if(c > 0 && !obstacles.at(r, c - 1) && !bombs.at(r, c - 1))
        move.at(p, ends.pos(r, c - 1)) = 1.0 / paths.at(r, c - 1);
      if(c < cols - 1 && !obstacles.at(r, c + 1) && !bombs.at(r, c + 1))
        move.at(p, ends.pos(r, c + 1)) = 1.0 / paths.at(r, c + 1);
      if(bombs.at(r, c)) {
        move.at(p, p) = 1.0;
      }
    }
  }
  for(int i = 0; i < pipes_count; ++i) {
    int from = ends.pos(pipes.at(i, 0) - 1, pipes.at(i, 1) - 1);
    int to = ends.pos(pipes.at(i, 2) - 1, pipes.at(i, 3) - 1);
    for(int j = 0; j < current.size(); ++j) {
      move.at(to, j) += move.at(from, j);
    }
  }
  current.at(ends.pos(start.at(0), start.at(1))) = 1.0;
  // std::cout << "bombs:\n" << bombs;
  // std::cout << std::setprecision(2);
  // std::cout << ends.pos(start.at(0), start.at(1)) << " : " << start << std::endl;
  // std::cout << current.reshape(rows, cols);
  // std::cout << std::endl;
  // for(int i = 0; i < 20; ++i) {
  //   TRACE_LINE(i);
  //   move = std::move(move * move);
  // }
  current = std::move(move.t() * move * current);
  TRACE_LINE(current.reshape(rows, cols));
  std::cout << (ends.reshape(1, current.size()) * current);
  return 0;
}
