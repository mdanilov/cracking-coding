// List of Depths: Given a binary tree, design an algorithm which creates a
// linked list of all the nodes at each depth (e.g., if you have a tree with
// depth 0, you'll have 0 linked lists). Hints: #107, #123, #135

#include <list>
#include <memory>
#include <vector>

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
struct TreeNode {
  int value;
  std::shared_ptr<TreeNode> left;
  std::shared_ptr<TreeNode> right;

  TreeNode(int v) : value(v) {}
};

void createLevelLinkedList(
    std::shared_ptr<TreeNode> root,
    std::vector<std::list<std::shared_ptr<TreeNode>>> &lists, int level) {
  if (root == nullptr)
    return; // base case

  if (lists.size() == level) { // level not contained in the list
    lists.emplace_back();
  }

  std::list<std::shared_ptr<TreeNode>> &list = lists[level];

  list.push_back(root);
  createLevelLinkedList(root->left, lists, level + 1);
  createLevelLinkedList(root->right, lists, level + 1);
}

std::vector<std::list<std::shared_ptr<TreeNode>>>
createLevelLinkedList_1(std::shared_ptr<TreeNode> root) {
  std::vector<std::list<std::shared_ptr<TreeNode>>> lists;
  createLevelLinkedList(root, lists, 0);
  return lists;
}

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
std::vector<std::list<std::shared_ptr<TreeNode>>>
createLevelLinkedList_2(std::shared_ptr<TreeNode> root) {
  std::vector<std::list<std::shared_ptr<TreeNode>>> result;
  /* Visit the root */
  std::list<std::shared_ptr<TreeNode>> current;
  if (root != nullptr) {
    current.push_back(root);
  }

  while (current.size() > 0) {
    result.push_back(current); // Add previous level
    std::list<std::shared_ptr<TreeNode>> &parents =
        result.back(); // Go to next level
    current.clear();
    for (std::shared_ptr<TreeNode> parent : parents) {
      /* Visit children */
      if (parent->left != nullptr) {
        current.push_back(parent->left);
      }
      if (parent->right != nullptr) {
        current.push_back(parent->right);
      }
    }
  }

  return result;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(ListOfDepthsTest, Trivial) {
  //               (0)
  //              /   \
  //            (1)   (2)
  //           /   \
  //         (3)   (4)
  //        /
  //      (5)
  auto root = std::make_shared<TreeNode>(0);
  root->left = std::make_shared<TreeNode>(1);
  root->right = std::make_shared<TreeNode>(2);
  root->left->left = std::make_shared<TreeNode>(3);
  root->left->right = std::make_shared<TreeNode>(4);
  root->left->left->left = std::make_shared<TreeNode>(5);

  std::vector<std::list<std::shared_ptr<TreeNode>>> expected_result = {
      {root},
      {root->left, root->right},
      {root->left->left, root->left->right},
      {root->left->left->left}};

  {
    auto result = createLevelLinkedList_1(root);
    EXPECT_EQ(result.size(), 4);
    for (size_t i = 0; i < result.size(); ++i) {
      EXPECT_EQ(result[i].size(), expected_result[i].size());
      auto it2 = expected_result[i].begin();
      auto it1 = result[i].begin();
      while (it1 != result[i].end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
      }
    }
  }

  {
    auto result = createLevelLinkedList_2(root);
    EXPECT_EQ(result.size(), 4);
    for (size_t i = 0; i < result.size(); ++i) {
      EXPECT_EQ(result[i].size(), expected_result[i].size());
      auto it2 = expected_result[i].begin();
      auto it1 = result[i].begin();
      while (it1 != result[i].end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
      }
    }
  }
}
