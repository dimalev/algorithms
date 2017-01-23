#ifndef IMAGE_LIBRARY_IMAGE_MANIP_H_
#define IMAGE_LIBRARY_IMAGE_MANIP_H_

#include "image.hpp"
#include "image_part.hpp"

namespace image_library {

  template<typename T, std::size_t D>
  Image<T, D> Scale(Image<T, D> &in_img, int factor) {
    int out_width = in_img.Width() / factor;
    if(in_img.Width() % factor != 0) out_width++;
    int out_height = in_img.Height() / factor;
    if(in_img.Height() % factor != 0) out_height++;
    Image<T, D> out_img{out_width, out_height};
    for(int i = 0; i < out_width; ++i) {
      for(int j = 0; j < out_height; ++j) {
        ImagePart<T, D> img_part{&in_img, i * factor, j * factor, factor, factor };
        out_img[i][j] = ImagePartAvarage(img_part);
      }
    }
    return out_img;
  }

  template<typename T, std::size_t D>
  Image<T, D> Transpose(const Image<T, D> &in_img) {
    Image<T, D> out_img{in_img.Height(), in_img.Width()};
    for(int i = 0; i < in_img.Width(); ++i) {
      for(int j = 0; j < in_img.Height(); ++j) {
        out_img[j][i] = in_img[i][j];
      }
    }
    return out_img;
  }

}

#endif
