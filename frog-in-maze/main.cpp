#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
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

  inline T at(int p) const {
    assert(p < size() && p >= 0);
    return data[p];
  }

  inline T& at(int p) {
    assert(p < size() && p >= 0);
    return data[p];
  }

  inline T at(int r, int c) const {
    assert(r < _rows && r >= 0);
    assert(c < _cols && c >= 0);
    return data[pos(r, c)];
  }

  inline T& at(int r, int c) {
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
          result.data[i * result._cols + j] +=
              data[i * _cols + k] *
              right.data[k * right._cols + j];
        }
      }
    }
    return result;
  }

  void square(double **buffer) {
    double *new_data = *buffer;
    for(int i = 0; i < _rows; ++i) {
      for(int j = 0; j < _cols; ++j) {
        int p = i * _cols + j;
        new_data[p] = 0;
        for(int k = 0; k < _cols; ++k) {
          new_data[p] +=
              data[i * _cols + k] * data[k * _cols + j];
        }
      }
    }
    double *temp = data;
    data = new_data;
    *buffer = temp;
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
  Mat<bool> obstacles{rows, cols}, bombs{rows, cols}, pipe_start{rows, cols};
  Mat<double> ends{rows, cols};
  Mat<double> current{rows * cols, 1};
  Mat<double> move{current.size(), current.size()};
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
          current.at(ends.pos(r, c)) = 1.0;
          break;
        case '%':
          ends.at(r, c) = 1.0;
          break;
      }
    }
  }
  std::map<int, int> pipes;
  for(int i = 0; i < pipes_count; ++i) {
    int rs, cs, re, ce;
    std::cin >> rs >> cs >> re >> ce;
    pipes[ends.pos(rs - 1, cs - 1)] = ends.pos(re - 1, ce - 1);
    pipes[ends.pos(re - 1, ce - 1)] = ends.pos(rs - 1, cs - 1);
  }
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      int p = ends.pos(r, c);
      if(obstacles.at(p)) continue;
      if(ends.at(p) || bombs.at(p)) {
        move.at(p, p) = 1.0;
        continue;
      }
      std::set<int> neigbours;
      if(r > 0 && !obstacles.at(r - 1, c)) {
        int e = ends.pos(r - 1, c);
        if(pipes.find(e) != pipes.end()) {
          neigbours.insert(pipes[e]);
        } else {
          neigbours.insert(e);
        }
      }
      if(r < rows - 1 && !obstacles.at(r + 1, c)) {
        int e = ends.pos(r + 1, c);
        if(pipes.find(e) != pipes.end()) {
          neigbours.insert(pipes[e]);
        } else {
          neigbours.insert(e);
        }
      }
      if(c > 0 && !obstacles.at(r, c - 1)) {
        int e = ends.pos(r, c - 1);
        if(pipes.find(e) != pipes.end()) {
          neigbours.insert(pipes[e]);
        } else {
          neigbours.insert(e);
        }
      }
      if(c < cols - 1 && !obstacles.at(r, c + 1)) {
        int e = ends.pos(r, c + 1);
        if(pipes.find(e) != pipes.end()) {
          neigbours.insert(pipes[e]);
        } else {
          neigbours.insert(e);
        }
      }
      // TRACE(r << ", " << c << ": ");
      if(neigbours.empty()) {
        move.at(p, p) = 1.0;
        // TRACE_LINE("empty");
      } else {
        double v = 1.0 / neigbours.size();
        for(auto out : neigbours) {
          move.at(out, p) = v;
        }
      }
    }
  }
  double *buffer = new double[move.size()];
  for(int i = 0; i < 17; ++i) {
    TRACE_LINE(i);
    move = std::move(move * move);
  }
  current = std::move(move * current);
  TRACE_LINE(current.reshape(rows, cols));
  std::cout << (ends.reshape(1, current.size()) * current);
  return 0;
}
