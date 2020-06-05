// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is
// 0, its entire row and column are set to O.
//
// Hints: #17, #74, #102

#include <vector>

using namespace std;

// Solution #1
// ------------------------------------------------------------------------------------------------

void nullifyRow(vector<vector<int>> &matrix, int row) {
  for (int j = 0; j < matrix[0].size(); j++) {
    matrix[row][j] = 0;
  }
}

void nullifyColumn(vector<vector<int>> &matrix, int col) {
  for (int i = 0; i < matrix.size(); i++) {
    matrix[i][col] = 0;
  }
}

void setZeros_1(vector<vector<int>> &matrix) {
  vector<bool> row(matrix.size());
  vector<bool> column(matrix[0].size());

  // Store the row and column index with value 0
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0) {
        row[i] = true;
        column[j] = true;
      }
    }
  }

  // Nullify rows
  for (int i = 0; i < row.size(); i++) {
    if (row[i])
      nullifyRow(matrix, i);
  }

  // Nullify columns
  for (int j = 0; j < column.size(); j++) {
    if (column[j])
      nullifyColumn(matrix, j);
  }
}

// Solution #2
// ------------------------------------------------------------------------------------------------

void setZeros_2(vector<vector<int>> &matrix) {
  bool rowHasZero = false;
  bool colHasZero = false;

  // Check if first row has a zero
  for (int j = 0; j < matrix[0].size(); j++) {
    if (matrix[0][j] == 0) {
      rowHasZero = true;
      break;
    }
  }

  // Check if first column has a zero
  for (int i = 0; i < matrix.size(); i++) {
    if (matrix[i][0] == 0) {
      colHasZero = true;
      break;
    }
  }

  // Check for zeros in the rest of the array
  for (int i = 1; i < matrix.size(); i++) {
    for (int j = 1; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
    }
  }

  // Nullify rows based on values in first column
  for (int i = 1; i < matrix.size(); i++) {
    if (matrix[i][0] == 0) {
      nullifyRow(matrix, i);
    }
  }

  // Nullify columns based on values in first row
  for (int j = 1; j < matrix[0].size(); j++) {
    if (matrix[0][j] == 0) {
      nullifyColumn(matrix, j);
    }
  }

  // Nullify first row
  if (rowHasZero) {
    nullifyRow(matrix, 0);
  }
  // Nullify first column
  if (colHasZero) {
    nullifyColumn(matrix, 0);
  }
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RotateMatrixTest, Trivial) {

  const vector<vector<int>> init = {
      {0, 1, 2, 3}, {4, 5, 0, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
  vector<vector<int>> b = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 9, 0, 11}, {0, 13, 0, 15}};
  vector<vector<int>> a;

  a = init;
  setZeros_1(a);
  ASSERT_EQ(a.size(), b.size()) << "Vectors x and y are of unequal length";
  for (int i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]) << "Vectors x and y differ at index " << i;
  }

  a = init;
  setZeros_2(a);
  ASSERT_EQ(a.size(), b.size()) << "Vectors x and y are of unequal length";
  for (int i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]) << "Vectors x and y differ at index " << i;
  }
}
