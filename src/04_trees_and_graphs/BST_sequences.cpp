// BST Sequences: A binary search tree was created by traversing through an
// array from left to right and inserting each element. Given a binary search
// tree with distinct elements, print all possible arrays that could have led to
// this tree.
//
// EXAMPLE
// Input:
//          (2)
//         /   \
//       (1)   (3)
//
// Output: {2, 1, 3}, {2, 3, 1}
//
// Hints: #39, #48, #66, #82

#include <list>
#include <vector>
#include <algorithm>

#include "utils/tree.h"

using namespace utils;

// Solution
// ------------------------------------------------------------------------------------------------
void weaveLists(std::list<int> first, std::list<int> second,
                std::vector<std::list<int>> &results, std::list<int> prefix) {
  /* One list is empty. Add remainder to [a cloned] prefix and store result. */
  if (first.size() == 0 || second.size() == 0) {
    std::list<int> result = prefix;
    for (auto e : first) {
      result.push_back(e);
    }
    for (auto e : second) {
      result.push_back(e);
    }
    results.push_back(result);
    return;
  }

  /* Recurse with head of first added to the prefix. Removing the head will damage
   * first, so we'll need to put it back where we found it afterwards. */
  int head_first = first.front();
  first.pop_front();
  prefix.push_back(head_first);
  weaveLists(first, second, results, prefix);
  prefix.pop_back();
  first.push_front(head_first);

  /* Do the same thing with second, damaging and then restoring the list.*/
  int head_second = second.front();
  second.pop_front();
  prefix.push_back(head_second);
  weaveLists(first, second, results, prefix);
  prefix.pop_back();
  second.push_front(head_second);
}

std::vector<std::list<int>> allSequences(TreeNodePtr node) {
  std::vector<std::list<int>> result;

  if (node == nullptr) {
    result.emplace_back();
    return result;
  }

  std::list<int> prefix;
  prefix.push_back(node->value);

  /* Recurse on left and right subtrees. */
  auto left_seq = allSequences(node->left);
  auto right_seq = allSequences(node->right);

  /* Weave together each list from the left and right sides. */
  for (auto left : left_seq) {
    for (auto right : right_seq) {
      std::vector<std::list<int>> weaved;
      weaveLists(left, right, weaved, prefix);
      for (auto weave : weaved) {
        result.push_back(weave);
      }
    }
  }

  return result;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(BSTSequencesTest, Trivial) {
  //               (3)
  //              /   \
  //            (1)   (4)
  //           /   \
  //         (0)   (2)
  auto root = std::make_shared<TreeNode>(3);
  root->left = std::make_shared<TreeNode>(1);
  root->right = std::make_shared<TreeNode>(4);
  root->left->left = std::make_shared<TreeNode>(0);
  root->left->right = std::make_shared<TreeNode>(2);

  std::vector<std::list<int>> sequences = {
    {3, 1, 0, 2, 4},
    {3, 1, 0, 4, 2},
    {3, 1, 4, 0, 2},
    {3, 4, 1, 0, 2},
    {3, 1, 2, 0, 4},
    {3, 1, 2, 4, 0},
    {3, 1, 4, 2, 0},
    {3, 4, 1, 2, 0}
  };

  auto results = allSequences(root);
  EXPECT_EQ(8, results.size());
  for (auto seq : results) {
    EXPECT_TRUE(std::find(sequences.begin(), sequences.end(), seq) != sequences.end());
  }
}
