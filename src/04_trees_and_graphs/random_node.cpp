// Random Node: You are implementing a binary tree class from scratch which, in
// addition to insert, find, and delete, has a method getRandomNode() which
// returns a random node from the tree. All nodes should be equally likely to be
// chosen. Design and implement an algorithm for getRandomNode, and explain how
// you would implement the rest of the methods. Hints: #42, #54, #62, #75, #89,
// #99, #112, #119

#include <cstdlib>
#include <ctime>
#include <memory>

// Solution #1
// Complexity (in balanced tree): time O(log N), where N is the number of nodes
// ------------------------------------------------------------------------------------------------
class TreeNode : public std::enable_shared_from_this<TreeNode> {
 public:
  TreeNode(int d) : data(d), size(1) {}

  int getSize() { return size; }
  int getData() { return data; }

  std::shared_ptr<TreeNode> getRandomNode() {
    int leftSize = (left == nullptr) ? 0 : left->getSize();
    std::srand(std::time(nullptr));
    int index = std::rand() / ((RAND_MAX + 1u) / size);
    if (index < leftSize) {
      return left->getRandomNode();
    } else if (index == leftSize) {
      return shared_from_this();
    } else {
      return right->getRandomNode();
    }
  }

  void insertInOrder(int d) {
    if (d <= data) {
      if (left == nullptr) {
        left = std::make_shared<TreeNode>(d);
      } else {
        left->insertInOrder(d);
      }
    } else {
      if (right == nullptr) {
        right = std::make_shared<TreeNode>(d);
      } else {
        right->insertInOrder(d);
      }
    }
    size++;
  }

  std::shared_ptr<TreeNode> find(int d) {
    if (d == data) {
      return shared_from_this();
    } else if (d <= data) {
      return left != nullptr ? left->find(d) : nullptr;
    } else if (d > data) {
      return right != nullptr ? right->find(d) : nullptr;
    }
    return nullptr;
  }

  std::shared_ptr<TreeNode> getIthNode(int i) {
    int leftSize = (left == nullptr) ? 0 : left->getSize();
    if (i < leftSize) {
      return left->getIthNode(i);
    } else if (i == leftSize) {
      return shared_from_this();
    } else {
      /* Skipping over leftSize + 1 nodes, to subtract them */
      return right->getIthNode(i - (leftSize + 1));
    }
  }

 private:
  int data;
  std::shared_ptr<TreeNode> left;
  std::shared_ptr<TreeNode> right;
  int size = 0;
};

// Solution #2
// Complexity (in balanced tree): time O(D), where D is the max depth of the
// tree
// ------------------------------------------------------------------------------------------------
class Tree {
 public:
  int getSize() { return root == nullptr ? 0 : root->getSize(); }

  std::shared_ptr<TreeNode> getRandomNode() {
    if (root == nullptr) return nullptr;

    std::srand(std::time(nullptr));
    int i = std::rand() / ((RAND_MAX + 1u) / getSize());
    return root->getIthNode(i);
  }

  void insertInOrder(int value) {
    if (root == nullptr) {
      root = std::make_shared<TreeNode>(value);
    } else {
      root->insertInOrder(value);
    }
  }

 private:
  std::shared_ptr<TreeNode> root = nullptr;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RandomNodeTest, Trivial) {
  {
    auto root = std::make_shared<TreeNode>(10);
    root->insertInOrder(1);
    root->insertInOrder(2);
    root->insertInOrder(4);
    root->insertInOrder(7);
    root->insertInOrder(3);
    root->insertInOrder(5);
    root->insertInOrder(8);
    root->insertInOrder(9);

    EXPECT_NE(root->find(root->getRandomNode()->getData()), nullptr);
  }

  {
    Tree tree;
    tree.insertInOrder(3);
    tree.insertInOrder(2);
    tree.insertInOrder(4);
    tree.insertInOrder(1);
    tree.insertInOrder(0);

    EXPECT_NE(tree.getRandomNode(), nullptr);
  }
}
