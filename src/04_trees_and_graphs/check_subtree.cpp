// Check Subtree: T1 and T2 are two very large binary trees, with Tl much bigger
// than T2. Create an algorith m to determine if T2 is a subtree of Tl . A tree
// T2 is a subtree ofTi if there exists a node n in Ti such that the subtree of
// n is identical to T2. That is, if you cut off the tree at node n, the two
// trees would be identical. Hints: #4, #11, #18, #31, #37

#include <string>

#include "utils/tree.h"

using namespace utils;

// Solution #1
// Complexity: time O(n + m), space O(n + m), where n and m are the number of
// nodes in T1 and T2, respectively.
// ------------------------------------------------------------------------------------------------
void getOrderstring(TreeNodePtr node, std::string &s) {
  if (node == nullptr) {
    s.append("X");  // Add null indicator
    return;
  }
  s.append(std::to_string(node->value));  // Add root
  getOrderstring(node->left, s);          // Add left
  getOrderstring(node->right, s);         // Add right
}

bool containsTree_1(TreeNodePtr t1, TreeNodePtr t2) {
  std::string string1;
  std::string string2;

  getOrderstring(t1, string1);
  getOrderstring(t2, string2);

  return string1.find(string2) != std::string::npos;
}

// Solution #2
// Complexity: time O(n + km), space O(lon(n) + log(m)), where k is the number
// of occurrences of T2's root in T1.
// ------------------------------------------------------------------------------------------------
bool matchTree(TreeNodePtr r1, TreeNodePtr r2) {
  if (r1 == nullptr && r2 == nullptr) {
    return true;  // nothing left in the subtree
  } else if (r1 == nullptr || r2 == nullptr) {
    return false;  // exactly tree is empty, therefore trees don't match
  } else if (r1->value != r2->value) {
    return false;  // data doesn't match
  } else {
    return matchTree(r1->left, r2->left) && matchTree(r1->right, r2->right);
  }
}

bool subTree(TreeNodePtr r1, TreeNodePtr r2) {
  if (r1 == nullptr) {
    return false;  // big tree empty & subtree still not found
  } else if (r1->value == r2->value && matchTree(r1, r2)) {
    return true;
  }
  return subTree(r1->left, r2) || subTree(r1->right, r2);
}

bool containsTree_2(TreeNodePtr t1, TreeNodePtr t2) {
  if (t2 == nullptr) return true;  // The empty tree is always a subtree
  return subTree(t1, t2);
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(CheckSubtreeTest, Trivial) {
  // t1 tree
  //               (0)
  //              /   \
  //            (1)   (2)
  //           /   \
  //         (3)   (4)
  //         /
  //       (5)
  auto t1 = std::make_shared<TreeNode>(0);
  t1->left = std::make_shared<TreeNode>(1);
  t1->right = std::make_shared<TreeNode>(2);
  t1->left->left = std::make_shared<TreeNode>(3);
  t1->left->right = std::make_shared<TreeNode>(4);
  t1->left->left->left = std::make_shared<TreeNode>(5);

  // t2 tree
  //            (1)
  //           /   \
  //         (3)   (4)
  auto t2 = std::make_shared<TreeNode>(1);
  t2->left = std::make_shared<TreeNode>(3);
  t2->right = std::make_shared<TreeNode>(4);

  EXPECT_FALSE(containsTree_1(t1, t2));
  EXPECT_FALSE(containsTree_2(t1, t2));

  // t2 becomes ->
  //            (1)
  //           /   \
  //         (3)   (4)
  //         /
  //       (5)
  t2->left->left = std::make_shared<TreeNode>(5);

  EXPECT_TRUE(containsTree_1(t1, t2));
  EXPECT_TRUE(containsTree_2(t1, t2));
}
