#ifndef IMAGE_LIBRARY_COL_PART_H_
#define IMAGE_LIBRARY_COL_PART_H_

#include <array>

#include "col.hpp"

namespace image_library {

  template<typename T, int D>
  class ColPart {
  protected:
    Col<T, D> *m_target;
    int m_start, m_size;
    typename Col<T, D>::cel_t m_polyfill;
  public:
    explicit ColPart() : m_target{nullptr}, m_polyfill{0} {}
    explicit ColPart(typename Col<T, D>::cel_t polyfill)
      : m_target{nullptr}, m_polyfill{polyfill}
    { }
    ColPart(Col<T, D> *target, int start, int size)
      : m_target{target}, m_polyfill{0}
      , m_start{start}, m_size{size}
    { }
    ColPart(Col<T, D> *target, int start, int size, typename Col<T, D>::cel_t polyfill)
      : m_target{target}
      , m_start{start}, m_size{size}
      , m_polyfill{polyfill}
    { }
    ColPart(ColPart &&from) :m_polyfill{from.m_polyfill} {
      m_start = from.m_start;
      m_size = from.m_size;
      m_target = from.m_target;
    }

    typename Col<T, D>::cel_t& operator[](int i) {
      if(m_target == nullptr) return m_polyfill;
      if(m_start + i < 0) return m_polyfill;
      if(m_start + i >= m_target->Size()) return m_polyfill;
      return (*m_target)[m_start + i];
    }

    const typename Col<T, D>::cel_t& operator[](int i) const {
      if(m_target == nullptr) return m_polyfill;
      if(m_start + i < 0) return m_polyfill;
      if(m_start + i >= m_target->Size()) return m_polyfill;
      return (*m_target)[m_start + i];
    }

    int Size() const { return m_size; }
  };

  template<typename T, unsigned int D>
  void operator+=(std::array<T, D>& left, const std::array<T, D>& right) {
    for(int i = 0; i < D; ++i) {
      left[i] += right[i];
    }
  }

  template<typename T, unsigned int D>
  void operator/=(std::array<T, D>& left, const int& divider) {
    for(int i = 0; i < D; ++i) {
      left[i] /= divider;
    }
  }

  template<typename T, int D>
  typename Col<T, D>::cel_t ColAvarage(const ColPart<T, D> &in_part) {
    typename Col<T, D>::cel_t aggregator{0};
    for(int i = 0; i < in_part.Size(); ++i) {
      aggregator += in_part[i];
    }
    aggregator /= in_part.Size();
    return aggregator;
  }

}
#endif
