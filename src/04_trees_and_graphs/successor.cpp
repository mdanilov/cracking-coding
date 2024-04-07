// Successor: Write an algorithm to find the "next" node (i.e., in-order
// successor) of a given node in a binary search tree. You may assume that each
// node has a link to its parent. Hints: #79, #91

#include "utils/tree.h"

using namespace utils;

// Solution
// ------------------------------------------------------------------------------------------------
TreeNodePtr leftMostChild(TreeNodePtr n) {
  if (n == nullptr) {
    return nullptr;
  }
  while (n->left != nullptr) {
    n = n->left;
  }
  return n;
}

TreeNodePtr inOrderSucc(TreeNodePtr n) {
  if (n == nullptr) {
    return nullptr;
  }

  /* Found right children -> return leftmost node of right subtree. */
  if (n->right != nullptr) {
    return leftMostChild(n->right);
  } else {
    TreeNodePtr q = n;
    TreeNodePtr x = q->parent;
    // Go up until we're on left instead of right
    while (x != nullptr && x->left != q) {
      q = x;
      x = x->parent;
    }
    return x;
  }
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(SuccessorTest, Trivial) {
  //               (3)
  //              /   \
  //            (1)   (4)
  //           /   \
  //         (0)   (2)
  auto root = std::make_shared<TreeNode>(3);
  root->left = std::make_shared<TreeNode>(1);
  root->left->parent = root;
  root->right = std::make_shared<TreeNode>(4);
  root->right->parent = root;
  root->left->left = std::make_shared<TreeNode>(0);
  root->left->left->parent = root->left;
  root->left->right = std::make_shared<TreeNode>(2);
  root->left->right->parent = root->left;

  EXPECT_EQ(root->left->right->value, inOrderSucc(root->left)->value);
  EXPECT_EQ(root->value, inOrderSucc(root->left->right)->value);
  EXPECT_EQ(nullptr, inOrderSucc(root->right));  // no successor for node 4
}
