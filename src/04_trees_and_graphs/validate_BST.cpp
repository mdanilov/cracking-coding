// Validate BST: Implement a function to check if a binary tree is a binary
// search tree. Hints: #35, #57, #86, #113, #128

#include <limits>

#include "utils/tree.h"

using namespace utils;

// Solution #1
// ------------------------------------------------------------------------------------------------
bool checkBST(TreeNodePtr root, int &last) {
  if (root == nullptr) return true;

  // Check / recurse left
  if (!checkBST(root->left, last)) return false;

  if (root->value <= last) {
    return false;
  }
  last = root->value;

  // Check / recurse right
  if (!checkBST(root->right, last)) return false;

  return true;  // All good!
}

bool checkBST_1(TreeNodePtr root) {
  int last = std::numeric_limits<int>::min();
  return checkBST(root, last);
}

// Solution #2
// Complexity: time O(N), space O(log N)
// ------------------------------------------------------------------------------------------------
bool checkBST(TreeNodePtr root, int min, int max) {
  if (root == nullptr) return true;

  if ((root->value <= min) || (root->value > max)) {
    return false;
  }

  if (!checkBST(root->left, min, root->value) ||
      !checkBST(root->right, root->value, max))
    return false;

  return true;
}

bool checkBST_2(TreeNodePtr root) {
  return checkBST(root, std::numeric_limits<int>::min(),
                  std::numeric_limits<int>::max());
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(ValidateBSTTest, Trivial) {
  //               (3)
  //              /   \
  //            (2)   (4)
  //           /   \
  //         (0)   (1)
  auto invalid_BST = std::make_shared<TreeNode>(3);
  invalid_BST->left = std::make_shared<TreeNode>(2);
  invalid_BST->right = std::make_shared<TreeNode>(4);
  invalid_BST->left->left = std::make_shared<TreeNode>(0);
  invalid_BST->left->right = std::make_shared<TreeNode>(1);

  EXPECT_FALSE(checkBST_1(invalid_BST));
  EXPECT_FALSE(checkBST_2(invalid_BST));

  //               (3)
  //              /   \
  //            (1)   (4)
  //           /   \
  //         (0)   (2)
  auto valid_BST = std::make_shared<TreeNode>(3);
  valid_BST->left = std::make_shared<TreeNode>(1);
  valid_BST->right = std::make_shared<TreeNode>(4);
  valid_BST->left->left = std::make_shared<TreeNode>(0);
  valid_BST->left->right = std::make_shared<TreeNode>(2);

  EXPECT_TRUE(checkBST_1(valid_BST));
  EXPECT_TRUE(checkBST_2(valid_BST));
}
