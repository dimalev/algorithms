#ifndef IMAGE_LIBRARY_IMAGE_IO_H_
#define IMAGE_LIBRARY_IMAGE_IO_H_

#include <sstream>
#include <iomanip>
#include <array>

#include "image.hpp"
#include "col.hpp"
#include "image_manip.hpp"

/**
 * Simple Input/Output for image library.
 *
 * Operates on standard strings. Delimiters are not configurable (still possible
 * to add this feature). Between rows - new line, between cols - space, between
 * values - comma.
 */

namespace image_library {

  /**
   * OUTPUT
   */

  template<typename T, std::size_t D>
  std::string ToDebugString(const Col<T, D> &in_col) {
    std::stringstream line;
    line << std::setprecision(4);
    for(int i = 0; i < in_col.Size(); ++i) {
      if(i > 0) line << " ";
      const typename Col<T, D>::cel_t &cell = in_col[i];
      for(int i = 0; i < D; ++i) {
        if(i != 0) line << ",";
        line << cell[i];
      }
    }
    return line.str();
  }

  template<typename T>
  std::string ToDebugString(const Col<T, 1> &in_col) {
    std::stringstream line;
    line << std::setprecision(4);
    for(int i = 0; i < in_col.Size(); ++i) {
      if(i > 0) line << " ";
      line << in_col[i];
    }
    return line.str();
  }

  template<typename T, std::size_t D>
  std::string ToDebugString(const Image<T, D> &in_img) {
    Image<T, D> in_img_transposed = Transpose(in_img);
    std::stringstream cols;
    for(int i = 0; i < in_img_transposed.Width(); ++i) {
      if(i > 0) cols << "\n";
      cols << ToDebugString(in_img_transposed[i]);
    }
    return cols.str();
  }

  /**
   * INPUT
   */

  constexpr int line_buffer_size = 1024;
  constexpr int number_buffer_size = 32;
  template<typename T, std::size_t D>
  void ColFromString(const std::string &in_data, Col<T, D> *out_col) {
    std::stringstream buffer(in_data);
    char line_buffer[line_buffer_size];
    for(int i = 0; i < out_col->Size(); ++i) {
      buffer.getline(line_buffer, line_buffer_size, ' ');
      std::stringstream numbers(line_buffer);
      for(int j = 0; j < D; ++j) {
        numbers >> (*out_col)[i][j];
        numbers.ignore(1); // we skip comma. not actually sure this is a good way
      }
    }
  }

  template<typename T>
  void ColFromString(const std::string &in_data, Col<T, 1> *out_col) {
    std::stringstream numbers(in_data);
    for(int i = 0; i < out_col->Size(); ++i) {
      numbers >> (*out_col)[i];
    }
  }

  constexpr int row_buffer_size = 1024;
  template<typename T, std::size_t D>
  void ImageFromString(const std::string &in_data, Image<T, D> *out_img) {
    Image<T, D> out_image_transposed{out_img->Height(), out_img->Width()};
    std::stringstream buffer(in_data);
    char row_buffer[row_buffer_size];
    for(int i = 0; i < out_img->Height(); ++i) {
      buffer.getline(row_buffer, row_buffer_size, '\n');
      std::string row(row_buffer);
      ColFromString(row, &out_image_transposed[i]);
    }
    (*out_img) = Transpose(out_image_transposed);
  }

}

#endif
