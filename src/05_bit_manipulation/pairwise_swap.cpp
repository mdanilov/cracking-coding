// Pairwise Swap: Write a program to swap odd and even bits in an integer with
// as few instructions as possible (e.g., bit 13 and bit 1 are swapped, bit 2
// and bit 3 are swapped, and so on).
//
// Hints: #145, #248, #328, #355

// Solution
// ------------------------------------------------------------------------------------------------
int swapOddEvenBits(int x) {
  return ((x & 0xAAAAAAAA) >> 1) | ((x & 0x55555555) << 1);
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(PairwiseSwapTest, Trivial) {
  EXPECT_EQ(swapOddEvenBits(0b01111010001101), 0b10110101001110);
}
