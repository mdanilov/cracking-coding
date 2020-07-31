// Check Balanced: Implement a function to check if a binary tree is balanced.
// For the purposes of this question, a balanced tree is defined to be a tree
// such that the heights of the two subtrees of any node never differ by more
// than one. Hints: #21, #33, #49, #105, #124

#include <limits>
#include <memory>

#include "utils/tree.h"

using namespace utils;

// Solution #1
// Complexity: time O(N log N)
// ------------------------------------------------------------------------------------------------
int getHeight(TreeNodePtr root) {
  if (root == nullptr)
    return -1; // Base case
  return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

bool isBalanced_1(TreeNodePtr root) {
  if (root == nullptr)
    return true; // Base case

  int height_diff = getHeight(root->left) - getHeight(root->right);
  if (std::abs(height_diff) > 1) {
    return false;
  } else { // Recurse
    return isBalanced_1(root->left) && isBalanced_1(root->right);
  }
}

// Solution #2
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
int checkHeight(TreeNodePtr root) {
  if (root == nullptr)
    return -1;

  int left_height = checkHeight(root->left);
  if (left_height == std::numeric_limits<int>::min())
    return std::numeric_limits<int>::min(); // Pass error up

  int right_height = checkHeight(root->right);
  if (right_height == std::numeric_limits<int>::min())
    return std::numeric_limits<int>::min(); // Pass error up

  int height_diff = left_height - right_height;
  if (std::abs(height_diff) > 1) {
    return std::numeric_limits<int>::min(); // Found error -> pass it back
  } else {
    return std::max(left_height, right_height) + 1;
  }
}

bool isBalanced_2(TreeNodePtr root) {
  return checkHeight(root) != std::numeric_limits<int>::min();
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(CheckBalancedTest, Trivial) {
  //               (0)
  //              /   \
  //            (1)   (2)
  //           /   \
  //         (3)   (4)
  auto root = std::make_shared<TreeNode>(0);
  root->left = std::make_shared<TreeNode>(1);
  root->right = std::make_shared<TreeNode>(2);
  root->left->left = std::make_shared<TreeNode>(3);
  root->left->right = std::make_shared<TreeNode>(4);

  EXPECT_TRUE(isBalanced_1(root));
  EXPECT_TRUE(isBalanced_2(root));

  //               (0)
  //              /   \
  //            (1)   (2)
  //           /   \
  //         (3)   (4)
  //        /
  //      (5)
  root->left->left->left = std::make_shared<TreeNode>(5);

  EXPECT_FALSE(isBalanced_1(root));
  EXPECT_FALSE(isBalanced_2(root));
}
