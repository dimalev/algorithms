#include <iostream>
#include <string>

#include "image.hpp"
#include "image_part.hpp"
#include "image_io.hpp"

#include "test_harness.hpp"

START_TEST(test_multi_col)
  /**
   * Test multi-valued case of column and column part representation.
   */
  image_library::Col<int, 3> col{10};
  ASSERT(col.Size() == 10, "Check Size");
  col[3][0] = 12;
  col[3][1] = 25;
  col[3][2] = 75;
  ASSERT(col[3][1] == 25, "Setting column item");

  image_library::ColPart<int, 3> part{&col, 2, 3};
  ASSERT(part[1][1] == 25, "Check column part");

  image_library::ColPart<int, 3> polyfilled_part{&col, -2, 5};
  std::cerr << "before testing column part " << polyfilled_part[1][1] << std::endl;
  ASSERT(polyfilled_part[1][1] == 0, "Column Part out of column size must be polyfilled");
END_TEST

START_TEST(test_mono_col)
  /**
   * Test single-valued column and column part specialization.
   */
  image_library::Col<int, 1> col{10};
  col[3] = 5;
  col[5] = 7;
  ASSERT(col[5] == 7, "Single column setting");

  image_library::ColPart<int, 1> part{&col, -2, 15};
  ASSERT(part[1] == 0, "Left column overflow must be polyfilled");
  ASSERT(part[14] == 0, "Right column overflow must be polyfilled");
  ASSERT(part[5] == 5, "Internal column part values must match original column");
  ASSERT(part[7] == 7, "Internal column part values must match original column");
END_TEST

START_TEST(test_image)
  image_library::Image<int, 1> rect{5,8};
  ASSERT(rect.Width() == 5, "Width should be good");
  ASSERT(rect.Height() == 8, "Height should be good");
  rect[4][7] = 1;
  rect[3][7] = 2;
  rect[3][6] = 3;
  rect[4][6] = 4;

  image_library::ImagePart<int, 1> view{&rect, 3, 6, 3, 3};
  ASSERT(view[0][0] == 3, "Left Top Corner from Image");
  ASSERT(view[1][1] == 1, "Center from Image");
  ASSERT(view[2][2] == 0, "Right Bottom Corner from polyfill");
  ASSERT(view[0][2] == 0, "Left Bottom Corner from polyfill");
  ASSERT(view[2][0] == 0, "Right Top Corner from polyfill");
END_TEST

START_TEST(test_col_io)
  /**
   * Test read from string.
   */
  std::string column{"2,1,5 7,3,2 6,4,9 2,3,5"};
  image_library::Col<int, 3> out_column{4};
  image_library::ColFromString(column, &out_column);
  ASSERT(out_column[2][1] == 4, "Value in column position");

  /**
   * Test write back to string.
   */
  std::string back_column = ToDebugString(out_column);
  ASSERT(column == back_column, "After writing column back to string should be same");
END_TEST

START_TEST(test_col_float_io)
  std::string input{"1.234,4.55,6.00 66.345,88.45,23.990 67.432,71.299,79.23"};
  image_library::Col<float, 3> column{3};
  image_library::ColFromString(input, &column);
  ASSERT(abs(column[1][1] - 88.45) < 1e-5, "Float should be read well");
END_TEST

START_TEST(test_col_avarage)
  std::string input{"1,20,300 2,30,100 3,10,200"};
  image_library::Col<int, 3> column{3};
  image_library::ColFromString(input, &column);
  auto avg = image_library::ColAvarage(image_library::ColPart<int, 3>{&column, 0, 3});
  ASSERT(avg[0] == 2, "First element of avarage");
  ASSERT(avg[1] == 20, "Second element of avarage");
  ASSERT(avg[2] == 200, "Third element of avarage");
END_TEST

START_TEST(test_scale)
  std::string input{"1 3 5 6\n3 1 1 12"};
  image_library::Image<int, 1> image{4, 2};
  image_library::ImageFromString(input, &image);
  image_library::Image<int, 1> scaled = image_library::Scale(image, 2);
  ASSERT(scaled.Width() == 2, "Width must be halved");
  ASSERT(scaled.Height() == 1, "Height must be halved");
  ASSERT(scaled[0][0] == 2, "Left half of rectangle");
  ASSERT(scaled[1][0] == 6, "Right half of rectangle");
END_TEST

START_TEST(test_image_copy)
  std::string input{"1,2 3,4 5,6 6,6\n3,1 1,3 1,5 12,2"};
  image_library::Image<int, 2> source_image{4, 2};
  image_library::ImageFromString(input, &source_image);
  image_library::Image<int, 2> dest_image = source_image.Copy();
  ASSERT(dest_image[2][1][1] == 5, "Copy must be successful");
  source_image[2][1][1] = 12;
  ASSERT(dest_image[2][1][1] == 5, "Copy must not suffer from source changing");
END_TEST

int main() {
  try {
    test_multi_col();
    test_mono_col();
    test_image();
    test_col_io();
    test_col_float_io();
    test_col_avarage();
    test_scale();
    test_image_copy();
  } catch(TestError& te) {
    std::cerr << "Test [" << current_test_name << "] failed " << te.reason() << std::endl;
  }
  return 0;
}
