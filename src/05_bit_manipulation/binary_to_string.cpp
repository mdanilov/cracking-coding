// Binary to String: Given a real number between 0 and 1 (e.g., 0.72) that is
// passed in as a double, print the binary representation. If the number cannot
// be represented accurately in binary with at most 32 characters, print
// "ERROR."
//
// Hints: #143, #167, #173, #269, #297

#include <string>

// Solution #1
// ------------------------------------------------------------------------------------------------
std::string printBinary_1(double num) {
  if (num >= 1 || num <= 0) {
    return std::string("ERROR");
  }

  std::string binary(".");
  while (num > 0) {
    /* Setting a limit on length: 32 characters */
    if (binary.length() >= 32) {
      return std::string("ERROR");
    }

    double r = num * 2;
    if (r >= 1) {
      binary += "1";
      num = r - 1;
    } else {
      binary += "0";
      num = r;
    }
  }
  return binary;
}

// Solution #2
// ------------------------------------------------------------------------------------------------
std::string printBinary_2(double num) {
  if (num >= 1 || num <= 0) {
    return std::string("ERROR");
  }

  std::string binary(".");
  double frac = 0.5;
  while (num > 0) {
    /* Setting a limit on length: 32 characters */
    if (binary.length() >= 32) {
      return std::string("ERROR");
    }

    if (num >= frac) {
      binary += "1";
      num -= frac;
    } else {
      binary += "0";
    }
    frac /= 2;
  }
  return binary;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(BinaryToStringTest, Trivial) {
  double n{0.625f}; // 0b101
  EXPECT_EQ(printBinary_1(n), ".101");
  EXPECT_EQ(printBinary_2(n), ".101");
}
