#include <iostream>
#include "gtest/gtest.h"

int Sum(int a, int b) {
  return a + abs(b);
}

TEST(SumTest, PositiveNumbers) {
  ASSERT_EQ(Sum(5, 7), 12) << "Positive numbers must work";
}

TEST(SumTest, NegativeNumbers) {
  ASSERT_EQ(Sum(5, -3), 2) << "Negfative number must work";
}

// int main() {
//   std::cout << "Hello, how are you?\n";
// }
