// Minimal Tree: Given a sorted (increasing order) array with unique integer
// elements, write an algo- rithm to create a binary search tree with minimal
// height. Hints: #19, #73, #176

#include <memory>
#include <vector>

// Solution
// ------------------------------------------------------------------------------------------------
struct TreeNode {
  int value;
  std::shared_ptr<TreeNode> left;
  std::shared_ptr<TreeNode> right;

  TreeNode(int v) : value(v) {}
};

std::shared_ptr<TreeNode> createMinimalBST(const std::vector<int> &arr,
                                           int start, int end) {
  if (end < start) {
    return nullptr;
  }
  int mid = (start + end) / 2;
  std::shared_ptr<TreeNode> n = std::make_shared<TreeNode>(arr[mid]);
  n->left = createMinimalBST(arr, start, mid - 1);
  n->left = createMinimalBST(arr, mid + 1, end);
  return n;
}

std::shared_ptr<TreeNode> createMinimalBST(const std::vector<int> &array) {
  return createMinimalBST(array, 0, array.size() - 1);
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(MinimalTreeTest, Trivial) {
  std::shared_ptr<TreeNode> n = createMinimalBST({0, 1, 2, 3, 4, 5, 6});
  int maxHeight = -1;
  std::function<void(std::shared_ptr<TreeNode>, int)> traversal;
  traversal = [&maxHeight, &traversal](std::shared_ptr<TreeNode> node,
                                       int height) {
    if (node != nullptr) {
      height++;
      maxHeight = std::max(maxHeight, height);
      traversal(node->left, height);
      traversal(node->right, height);
    }
  };
  traversal(n, -1);
  EXPECT_EQ(2, maxHeight);
}
