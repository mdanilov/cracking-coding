// Paths with Sum: You are given a binary tree in which each node contains an
// integer value (which might be positive or negative). Design an algorithm to
// count the number of paths that sum to a given value. The path does not need
// to start or end at the root or a leaf, but it must go downwards (traveling
// only from parent nodes to child nodes). Hints: #6, #14, #52, #68, #77, #87,
// #94, #103, #108, #115

#include <map>

#include "utils/tree.h"

using namespace utils;

// Solution #1
// Complexity (in balanced tree): time O(N log N)
// ------------------------------------------------------------------------------------------------
/* Returns the number of paths with this sum starting from this node */
int countPathsWithSumFromNode(TreeNodePtr node, int targetSum, int currentSum) {
  if (node == nullptr)
    return 0;

  currentSum += node->value;

  int totalPaths = 0;
  if (currentSum == targetSum) { // Found a path from the root
    totalPaths++;
  }

  totalPaths += countPathsWithSumFromNode(node->left, targetSum, currentSum);
  totalPaths += countPathsWithSumFromNode(node->right, targetSum, currentSum);
  return totalPaths;
}

int countPathsWithSum_1(TreeNodePtr root, int targetSum) {
  if (root == nullptr)
    return 0;

  /* Count paths with sum starting from the root */
  int pathsFromRoot = countPathsWithSumFromNode(root, targetSum, 0);

  /* Try the nodes on the left and right */
  int pathsOnLeft = countPathsWithSum_1(root->left, targetSum);
  int pathsOnRight = countPathsWithSum_1(root->right, targetSum);

  return pathsFromRoot + pathsOnLeft + pathsOnRight;
}

// Solution #2
// Complexity: time O(N) (balanced tree O(log N)), space O(n)
// ------------------------------------------------------------------------------------------------
void incrementHashTable(std::map<int, int> &hashTable, int key, int delta) {
  if (hashTable.find(key) == hashTable.end())
    hashTable[key] = 0;
  int newCount = hashTable[key] + delta;
  if (newCount == 0) { // Remove when zero to reduce space usage
    hashTable.erase(key);
  } else {
    hashTable[key] = newCount;
  }
}

int countPathsWithSum(TreeNodePtr node, int targetSum, int runningSum,
                      std::map<int, int> &pathCount) {
  if (node == nullptr)
    return 0; // Base case

  /* Count paths with sum ending at the current node. */
  runningSum += node->value;
  int sum = runningSum - targetSum;
  if (pathCount.find(sum) == pathCount.end())
    pathCount[sum] = 0;
  int totalPaths = pathCount[sum];

  /* If runningSum equals targetSum, then one additional path starts at root
   * Add in this path. */
  if (runningSum == targetSum) {
    totalPaths++;
  }

  /* Increment pathCount, recurse, then decement pathCount */
  incrementHashTable(pathCount, runningSum, 1); // Increment pathCount
  totalPaths += countPathsWithSum(node->left, targetSum, runningSum, pathCount);
  totalPaths += countPathsWithSum(node->right, targetSum, runningSum, pathCount);
  incrementHashTable(pathCount, runningSum, -1); // Decrement pathCount

  return totalPaths;
}

int countPathsWithSum_2(TreeNodePtr root, int targetSum) {
  std::map<int, int> hashTable;
  return countPathsWithSum(root, targetSum, 0, hashTable);
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(PathsWithSumTest, Trivial) {
  // root ->
  //                 (10)
  //              /        \
  //            (5)       (-3)
  //           /   \          \
  //         (3)   (2)        (11)
  //        /   \     \
  //      (3)   (-2)  (1)
  auto root = std::make_shared<TreeNode>(10);
  root->left = std::make_shared<TreeNode>(5);
  root->right = std::make_shared<TreeNode>(-3);
  root->left->left = std::make_shared<TreeNode>(3);
  root->left->right = std::make_shared<TreeNode>(2);
  root->right->right = std::make_shared<TreeNode>(11);
  root->left->left->left = std::make_shared<TreeNode>(3);
  root->left->left->right = std::make_shared<TreeNode>(-2);
  root->left->right->right = std::make_shared<TreeNode>(1);

  EXPECT_EQ(countPathsWithSum_1(root, 8), 3);
  EXPECT_EQ(countPathsWithSum_2(root, 8), 3);
}
