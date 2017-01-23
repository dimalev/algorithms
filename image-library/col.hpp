#ifndef IMAGE_LIBRARY_COL_H_
#define IMAGE_LIBRARY_COL_H_

#include <array>
#include <vector>

namespace image_library {

  template<typename T, std::size_t D>
  class Col {
  public:
    using cel_t = std::array<T, D>;
    Col(int size) { m_Data.resize(size); }

    cel_t& operator[](int i) { return m_Data[i]; }
    const cel_t& operator[](int i) const { return m_Data[i]; }

    void operator=(const Col<T, 1> &in_col) {
      m_Data = in_col.m_Data;
    }

    int Size() const { return m_Data.size(); }
  protected:
    std::vector<cel_t> m_Data;
  };

  template<typename T>
  class Col<T, 1> {
  public:
    using cel_t = T;
    Col(int size) { m_Data.resize(size); }
    cel_t& operator[](int i) { return m_Data[i]; }
    const cel_t& operator[](int i) const { return m_Data[i]; }
    int Size() const { return m_Data.size(); }

    void operator=(const Col<T, 1> &in_col) {
      m_Data = in_col.m_Data;
    }
  protected:
    std::vector<cel_t> m_Data;
  };

}
#endif
