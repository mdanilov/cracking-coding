// Insertion: You are given two 32-bit numbers, Nand M, and two bit positions, i
// and j. Write a method to insert M into N such that M starts at bit j and ends
// at bit i. You can assume that the bits j through i have enough space to fit
// all of M. That is, if M = 10011, you can assume that there are at least 5
// bits between j and i. You would not, for example, have j = 3 and i = 2,
// because M could not fully fit between bit 3 and bit 2.
//
// EXAMPLE
// Input: N = 10000000000, M = 10011, i = 2, j = 6
// Output: N = 10001001100
//
// Hints: #137, #169, #215

// Solution
// ------------------------------------------------------------------------------------------------
int updateBits(int n, int m, int i, int j) {
  /* Create a mask to clear bits i through j in n. EXAMPLE: i = 2, j = 4. Result
   * should be 11100011. For simplicity, we'll use just 8 bits for the example.
   */
  int allOnes = ~0;  // will equal sequence of all 1s

  // 1s before position j, then 0s. left = 11100000
  int left = allOnes << (j + 1);

  // 1's after position i, right = 00000011
  int right = ((1 << i) - 1);

  // All 1s, except for 0s between i and j. mask = 11100011
  int mask = left | right;

  /* Clear bits j through i then put m in there */
  int n_cleared = n & mask;      // Clear bits j through i.
  int m_shifted = m << i;        // Move m into correct position.
  return n_cleared | m_shifted;  // OR them, an we're done!
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(InsertionTest, Trivial) {
  int n = 0b10000000000;
  int m = 0b10011;
  EXPECT_EQ(updateBits(n, m, 2, 6), 0b10001001100);
}
