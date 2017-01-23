#ifndef IMAGE_LIBRARY_IMAGE_H_
#define IMAGE_LIBRARY_IMAGE_H_

#include <vector>

#include "col.hpp"

namespace image_library {

  template<typename T, int D>
  class Image {
    std::vector<Col<T,D>> m_Cols;
    int m_Rows;
  public:
    Image(int W, int H) {
      m_Rows = H;
      for(int i = 0; i < W; ++i) {
        m_Cols.emplace_back(m_Rows);
      }
    }
    int Width() const { return m_Cols.size(); };
    int Height() const { return m_Rows; };
    Col<T, D>& operator[](int c) { return m_Cols[c]; }
    const Col<T, D>& operator[](int c) const { return m_Cols[c]; }

    void operator=(const Image<T, D> &in_image) {
      m_Cols = in_image.m_Cols;
    }

    Image<T, D> Copy() const {
      Image<T,D> new_image{*this};
      return new_image;
    }
  };

}

#endif
