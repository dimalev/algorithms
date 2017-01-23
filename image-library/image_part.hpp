#ifndef IMAGE_LIBRARY_IMAGE_PART_H_
#define IMAGE_LIBRARY_IMAGE_PART_H_

#include <vector>

#include "image.hpp"
#include "col_part.hpp"

namespace image_library {

  template<typename T, int D>
  class ImagePart {
    Image<T, D> *m_target;
    int m_start_col, m_start_row, m_cols, m_rows;
  public:
    ImagePart(Image<T, D>* image, int x, int y, int W, int H)
      : m_target{image}, m_start_col{x}, m_start_row{y}, m_cols{W}, m_rows{H}
    { }
    int Width() const { return m_cols; };
    int Height() const { return m_rows; };
    ColPart<T, D> operator[](int c) {
      if(m_start_col + c < 0) return ColPart<T, D>{};
      if(m_start_col + c >= m_target->Width()) return ColPart<T, D>{};
      return ColPart<T, D>{&(*m_target)[m_start_col + c], m_start_row, m_rows};
    }
    const ColPart<T, D> operator[](int c) const {
      if(m_start_col + c < 0) return ColPart<T, D>{};
      if(m_start_col + c >= m_target->Width()) return ColPart<T, D>{};
      return ColPart<T, D>{&(*m_target)[m_start_col + c], m_start_row, m_rows};
    }
  };

  template<typename T, int D>
  typename Col<T, D>::cel_t ImagePartAvarage(const ImagePart<T, D> &in_img) {
    typename Col<T, D>::cel_t aggregator{0};
    for(int i = 0; i < in_img.Width(); ++i) {
      aggregator += ColAvarage(in_img[i]);
    }
    return aggregator / in_img.Width();
  }

}

#endif
