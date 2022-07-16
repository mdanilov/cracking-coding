// Delete Middle Node: Implement an algorithm to delete a node in the middle
// (i.e., any node but the first and last node, not necessarily the exact
// middle) of a singly linked list, given only access to that node.
//
// EXAMPLE
// Input: the node c from the linked list a -> b -> c -> d -> e -> f
// Result: nothing is returned, but the new linked list looks like a -> b -> d
// -> e -> f

// Hints: #72

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(1), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T>
bool deleteNode(typename ForwardList<T>::NodePtr n) {
  if (n == nullptr || n->next == nullptr) {
    return false;  // Failure
  }
  typename ForwardList<T>::NodePtr next = n->next;
  n->data = next->data;
  n->next = next->next;
  return true;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(DeleteMiddleNodeTest, Trivial) {
  ForwardList<char> list({'a', 'b', 'c', 'd', 'e', 'f'});
  ForwardList<char> expected_list({'a', 'b', 'd', 'e', 'f'});

  typename ForwardList<char>::NodePtr c = list.head->next->next;
  deleteNode<char>(c);
  EXPECT_EQ(list, expected_list);
}
