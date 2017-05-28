#include <cstring>
#include <cassert>

class square {
  char *letters;
  int _cols, _rows;
 public:
  square(int rows, int cols)
      : _rows{rows}, _cols{cols}, letters{new char[rows * cols]} {}
  square(const square &other)
      : _rows{other._rows}, _cols{other._cols},
        letters{new char[other._rows * other._cols]} {
    std::memcpy(letters, other.letters, _rows * _cols);
  }
  square(std::initializer_list<std::initializer_list<char>> source) {
    _rows = source.size();
    assert(_rows > 0);
    int r = 0;
    for(auto line : source) {
      if (r == 0) {
        _cols = line.size();
        letters = new char(_rows * _cols);
      }
      assert(_cols == line.size());
      int c = 0;
      for(auto cell : line) {
        at(r, c) = cell;
        ++c;
      }
      ++r;
    }
  }
  square(square &&other)
      : _rows{other._rows}, _cols{other._cols}, letters{other.letters} {
    other.letters = nullptr;
  }
  ~square() {
    if(letters != nullptr) {
      delete[] letters;
    }
  }
  inline char& at(int r, int c) {
    return letters[r * _cols + c];
  }
  inline char at(int r, int c) const {
    return letters[r * _cols + c];
  }
  bool compare_at(const square &other, int row, int col) const {
    if(row + other._rows >= _rows) return false;
    if(col + other._cols >= _cols) return false;
    for(int r = 0; r < other._rows; ++r) {
      for(int c = 0; c < other._cols; ++c) {
        if(other.at(r, c) != at(row + r, col + c))
          return false;
      }
    }
    return true;
  }
  bool operator==(const square &other) const {
    if(other._rows != _rows || other._cols != _cols)
      return false;
    for(int r = 0; r < _rows; ++r) {
      for(int c = 0; c < _cols; ++c) {
        if(other.at(r, c) != at(r, c))
          return false;
      }
    }
    return true;
  }
  int rows() const { return _rows; }
  int cols() const { return _cols; }
};
