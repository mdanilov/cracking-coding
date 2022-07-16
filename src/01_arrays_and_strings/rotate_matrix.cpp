// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel
// in the image is 4 bytes, write a method to rotate the image by 90 degrees.
// (an you do this in place?
//
// Hints: #51, #100

#include <memory>
#include <string>

using namespace std;

// Solution #1
// ------------------------------------------------------------------------------------------------

template <size_t n>
void rotate(int (&matrix)[n][n]) {
  for (int layer = 0; layer < n / 2; layer++) {
    int first = layer;
    int last = n - 1 - layer;
    for (int i = first; i < last; i++) {
      int offset = i - first;
      int top = matrix[first][i];  // save top
      // left->top
      matrix[first][i] = matrix[last - offset][first];
      // bottom->left
      matrix[last - offset][first] = matrix[last][last - offset];
      // right->bottom
      matrix[last][last - offset] = matrix[i][last];
      // top->right
      matrix[i][last] = top;  // right <- saved top;
    }
  }
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RotateMatrixTest, Trivial) {
  int a[4][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
  int b[4][4] = {{12, 8, 4, 0}, {13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}};

  rotate<4>(a);
  EXPECT_TRUE(0 == memcmp(a, b, sizeof(a)));
}
