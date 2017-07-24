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
  bool _owner;
  int _row_stride, _col_stride;
  const int _rows, _cols;
 public:
  Mat(int _rows, int _cols)
      : _rows{_rows}, _cols{_cols}, data{new T[_rows * _cols]}, _owner{true},
        _row_stride{_cols}, _col_stride{1}
  {
    std::fill(data, data + size(), 0);
  }

  Mat(Mat &other, int dr, int dc, int _rows, int _cols, int _row_stride,
      int _col_stride) : _rows{_rows}, _cols{_cols}, _row_stride{_row_stride},
                         _col_stride{_col_stride}, _owner{false},
                         data{other.data + other.pos(dr, dc)}
  {
  }

  Mat(const Mat &other)
      : _rows{other._rows}, _cols{other._cols},
        _owner{other._owner}, _row_stride{other._row_stride},
        _col_stride{other._col_stride}
  {
    if(other._owner) {
      data = new T[_rows * _cols];
      std::copy_n(other.data, data, size());
    } else {
      data = other.data;
    }
  }

  Mat(Mat &&other)
      : _rows{other._rows}, _cols{other._cols}, data{other.data},
        _owner{other._owner}, _row_stride{other._row_stride},
        _col_stride{other._col_stride}
  {
    other.data = nullptr;
  }

  virtual ~Mat() {
    if(data != nullptr && _owner) {
      delete[] data;
    }
  }

  inline int size() const { return _rows * _cols; }
  inline int rows() const { return _rows; }
  inline int cols() const { return _cols; }

  inline int pos(int r, int c) const {
    return r * _row_stride + c * _col_stride;
  }

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

  Mat operator+(const Mat &right) const {
    if(_cols != right._cols || _rows != right._rows) throw "Size mismatch";
    Mat result{_rows, _cols};
    for(int i = 0; i < size(); ++i) result.at(i) = at(i) + right.at(i);
    return result;
  }

  Mat operator*(Mat &right) {
    if(_cols != right._rows) throw "Size mismatch";
    Mat result{_rows, right._cols};
    if(std::min(std::min(_rows, _cols),
                std::min(right._rows, right._cols)) <= 2) {
      for(int i = 0; i < _rows; ++i) {
        for(int j = 0; j < right._cols; ++j) {
          result.at(i, j) = 0;
          for(int k = 0; k < _cols; ++k) {
            result.at(i, j) += at(i, k) * right.at(k, j);
          }
        }
      }
    } else {
      int C1rows = result._rows / 2;
      int C1cols = result._cols / 2;
      Mat C1{result, 0, 0,
            C1rows, C1cols,
            result._row_stride, result._col_stride};
      Mat C2{result, 0, C1cols,
            C1rows, result._cols - C1cols,
            result._row_stride, result._col_stride};
      Mat C3{result,
            C1rows, 0,
            result._rows - C1rows, C1cols,
            result._row_stride, result._col_stride};
      Mat C4{result,
            C1rows, C1cols,
            result._rows - C1rows, result._cols - C1cols,
            result._row_stride, result._col_stride};

      int A1rows = this->_rows / 2;
      int A1cols = this->_cols / 2;
      Mat A1{*this, 0, 0,
            A1rows, A1cols,
            this->_row_stride, this->_col_stride};
      Mat A2{*this, 0, A1cols,
            A1rows, this->_cols - A1cols,
            this->_row_stride, this->_col_stride};
      Mat A3{*this,
            A1rows, 0,
            this->_rows - A1rows, A1cols,
            this->_row_stride, this->_col_stride};
      Mat A4{*this,
            A1rows, A1cols,
            this->_rows - A1rows, this->_cols - A1cols,
            this->_row_stride, this->_col_stride};

      int B1rows = right._rows / 2;
      int B1cols = right._cols / 2;
      Mat B1{right, 0, 0,
            B1rows, B1cols,
            right._row_stride, right._col_stride};
      Mat B2{right, 0, B1cols,
            B1rows, right._cols - B1cols,
            right._row_stride, right._col_stride};
      Mat B3{right,
            B1rows, 0,
            right._rows - B1rows, B1cols,
            right._row_stride, right._col_stride};
      Mat B4{right,
            B1rows, B1cols,
            right._rows - B1rows, right._cols - B1cols,
            right._row_stride, right._col_stride};

      C1 = A1 * B1 + A2 * B3;
      C2 = A1 * B2 + A2 * B4;
      C3 = A3 * B1 + A4 * B3;
      C4 = A3 * B2 + A4 * B4;
    }
    return result;
  }

  Mat& operator=(const Mat &right) {
    if(_cols != right._cols || _rows != right._rows) throw "Size mismatch";
    if(_owner && right._owner) {
      std::copy_n(right.data, data, size());
    } else {
      for(int r = 0; r < _rows; ++r)
        for(int c = 0; c < _cols; ++c)
          at(r, c) = right.at(r, c);
    }
    return *this;
  }

  Mat& operator=(Mat &&right) {
    if(_cols != right._cols || _rows != right._rows) throw "Size mismatch";
    if(_owner) {
      delete[] data;
      data = right.data;
      _owner = right._owner;
      _row_stride = right._row_stride;
      _col_stride = right._col_stride;
      right.data = nullptr;
    } else {
      for(int r = 0; r < _rows; ++r)
        for(int c = 0; c < _cols; ++c)
          at(r, c) = right.at(r, c);
    }
    return *this;
  }

  Mat reshape(int new_rows, int new_cols) {
    if(new_rows * new_cols != size()) throw "Size mismatch";
    return Mat{*this, 0, 0, 1, size(), 0, 1};
  }

  Mat row(int r) {
    return Mat{*this, r, 0, 1, _cols, 0, 1};
  }

  Mat col(int c) {
    return Mat{*this, 0, c, _rows, 1, _row_stride, 0};
  }

  Mat t() {
    return Mat{*this, 0, 0, _cols, _rows, _col_stride, _row_stride};
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
  test_header("matrix sum");
  std::cin >> rows >> cols;
  Mat<int> sum_left{rows, cols};
  std::cin >> sum_left;
  std::cin >> rows >> cols;
  Mat<int> sum_right{rows, cols};
  std::cin >> sum_right;
  std::cout << (sum_left + sum_right);
  test_header("simple matrix multiply");
  std::cin >> rows >> cols;
  Mat<int> simple_left{rows, cols};
  std::cin >> simple_left;
  std::cin >> rows >> cols;
  Mat<int> simple_right{rows, cols};
  std::cin >> simple_right;
  std::cout << (simple_left * simple_right);
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
  for(int i = 0; i < 20; ++i) {
    TRACE_LINE(i);
    move = move * move;
  }
  current = std::move(move.t() * move * current);
  // TRACE_LINE(current.reshape(rows, cols));
  std::cout << (ends.reshape(1, current.size()) * current);
  return 0;
}
