// Conversion: Write a function to determine the number of bits you would need
// to flip to convert integer A to integer B.
//
// EXAMPLE
// Input: 29 (or: 11101), 15 (or: 01111)
// Output: 2
//
// Hints: #336, #369

// Solution #1
// ------------------------------------------------------------------------------------------------
int bitSwapRequired_1(int a, int b) {
  int count = 0;
  for (int c = a ^ b; c != 0; c = c >> 1) {
    count += c & 1;
  }
  return count;
}

// Solution #2
// ------------------------------------------------------------------------------------------------
int bitSwapRequired_2(int a, int b) {
  int count = 0;
  for (int c = a ^ b; c != 0; c = c & (c - 1)) {
    count++;
  }
  return count;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(ConversionTest, Trivial) {
  EXPECT_EQ(bitSwapRequired_1(29, 15), 2);
  EXPECT_EQ(bitSwapRequired_2(29, 15), 2);
}
