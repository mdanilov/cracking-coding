// First Common Ancestor: Design an algorithm and write code to find the first
// common ancestor of two nodes in a binary tree. Avoid storing additional nodes
// in a data structure. NOTE: This is not necessarily a binary search tree.
// Hints: # 10, #16, #28, #36, #46, #70, #80, #96

#include <cmath>

#include "utils/tree.h"

using namespace utils;

// Solution #1
// Complexity: time O(d), where d is the depth of the deeper node
// ------------------------------------------------------------------------------------------------
TreeNodePtr goUpBy(TreeNodePtr node, int delta) {
  while (delta > 0 && node != nullptr) {
    node = node->parent;
    delta--;
  }
  return node;
}

int depth(TreeNodePtr node) {
  int depth = 0;
  while (node != nullptr) {
    node = node->parent;
    depth++;
  }
  return depth;
}

TreeNodePtr commonAncestor_1(TreeNodePtr p, TreeNodePtr q) {
  int delta = depth(p) - depth(q);           // get difference in depths
  TreeNodePtr first = delta > 0 ? q : p;     // get shallower node
  TreeNodePtr second = delta > 0 ? p : q;    // get deeper node
  second = goUpBy(second, std::abs(delta));  // move deeper node up

  /* Find where paths intersect */
  while (first != second && first != nullptr && second != nullptr) {
    first = first->parent;
    second = second->parent;
  }

  return first == nullptr || second == nullptr ? nullptr : first;
}

// Solution #2
// Complexity: time O(t), where t is the size of the subtree for the first
// common ancestor
// ------------------------------------------------------------------------------------------------
TreeNodePtr getSibling(TreeNodePtr node) {
  if (node == nullptr || node->parent == nullptr) {
    return nullptr;
  }

  TreeNodePtr parent = node->parent;
  return parent->left == node ? parent->right : parent->left;
}

bool covers(TreeNodePtr root, TreeNodePtr p) {
  if (root == nullptr) return false;
  if (root == p) return true;
  return covers(root->left, p) || covers(root->right, p);
}

TreeNodePtr commonAncestor_2(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q) {
  /* Check if either node is not in the tree, or if one covers the other. */
  if (!covers(root, p) || !covers(root, q)) {
    return nullptr;
  } else if (covers(p, q)) {
    return p;
  } else if (covers(q, p)) {
    return q;
  }

  /* Traverse upwards until you find a node that covers q. */
  TreeNodePtr sibling = getSibling(p);
  TreeNodePtr parent = p->parent;
  while (!covers(sibling, q)) {
    sibling = getSibling(parent);
    parent = parent->parent;
  }

  return parent;
}

// Solution #3
// Complexity: time O(N) on balanced tree
// ------------------------------------------------------------------------------------------------
TreeNodePtr ancestorHelper(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q) {
  if (root == nullptr || p == nullptr || q == nullptr) {
    return root;
  }

  bool p_is_on_left = covers(root->left, p);
  bool q_is_on_left = covers(root->left, q);
  if (p_is_on_left != q_is_on_left) {  // Nodes are on different side
    return root;
  }

  TreeNodePtr child_side = p_is_on_left ? root->left : root->right;
  return ancestorHelper(child_side, p, q);
}

TreeNodePtr commonAncestor_3(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q) {
  /* Error check - one node is not in the tree. */
  if (!covers(root, p) || !covers(root, q)) {
    return nullptr;
  }
  return ancestorHelper(root, p, q);
}

// Solution #4
// Complexity: time O(N) on balanced tree
// ------------------------------------------------------------------------------------------------
struct Result {
  TreeNodePtr node;
  bool is_ancestor;

  Result(TreeNodePtr n, bool is_anc) : node(n), is_ancestor(is_anc) {}
};

Result commonAncHelper(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q) {
  if (root == nullptr) return Result(nullptr, false);

  if (root == p && root == q) {
    return Result(root, true);
  }

  Result rx = commonAncHelper(root->left, p, q);
  if (rx.is_ancestor) {
    return rx;
  }

  Result ry = commonAncHelper(root->right, p, q);
  if (rx.is_ancestor) {
    return ry;
  }

  if (rx.node != nullptr && ry.node != nullptr) {
    return Result(root, true);  // This is the common ancestor
  } else if (root == p || root == q) {
    /* If we're currently at p or q, and we also found one of those nodes in a
     * subtree, then this is truly an ancestor and the flag should be true. */
    bool is_ancestor = rx.node != nullptr || ry.node != nullptr;
    return Result(root, is_ancestor);
  } else {
    return Result(rx.node != nullptr ? rx.node : ry.node, false);
  }
}

TreeNodePtr commonAncestor_4(TreeNodePtr root, TreeNodePtr p, TreeNodePtr q) {
  Result r = commonAncHelper(root, p, q);
  if (r.is_ancestor) {
    return r.node;
  }
  return nullptr;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(FirstCommonAncestorTest, Trivial) {
  //               (3)
  //              /   \
  //            (1)   (4)
  //           /   \
  //         (0)   (2)
  auto root = std::make_shared<TreeNode>(3);
  auto node_1 = std::make_shared<TreeNode>(1);
  root->left = node_1;
  node_1->parent = root;
  auto node_4 = std::make_shared<TreeNode>(4);
  root->right = node_4;
  node_4->parent = root;
  auto node_0 = std::make_shared<TreeNode>(0);
  node_1->left = node_0;
  node_0->parent = node_1;
  auto node_2 = std::make_shared<TreeNode>(2);
  node_1->right = node_2;
  node_2->parent = node_1;

  TreeNodePtr ancestor;
  ancestor = commonAncestor_1(node_4, node_0);
  EXPECT_EQ(ancestor, root);
  ancestor = commonAncestor_2(root, node_4, node_0);
  EXPECT_EQ(ancestor, root);
  ancestor = commonAncestor_3(root, node_4, node_0);
  EXPECT_EQ(ancestor, root);
  ancestor = commonAncestor_4(root, node_4, node_0);
  EXPECT_EQ(ancestor, root);
}
