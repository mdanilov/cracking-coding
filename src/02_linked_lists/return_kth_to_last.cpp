// Return Kth to Last: Implement an algorithm to find the kth to last element of
// a singly linked list.

// Hints: #8, #25, #47, #67, #126

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T>
typename ForwardList<T>::NodePtr
nthToLast(typename ForwardList<T>::NodePtr head, int k, int &i) {
  if (head == nullptr) {
    return nullptr;
  }
  typename ForwardList<T>::NodePtr nd = nthToLast<T>(head->next, k, i);
  i = i + 1;
  if (i == k) {
    return head;
  }
  return nd;
}

template <typename T>
typename ForwardList<T>::NodePtr nthToLast(ForwardList<T> &l, int k) {
  int i = 0;
  return nthToLast<T>(l.head, k, i);
}

// Solution #2
// Complexity: time O(N), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T>
typename ForwardList<T>::NodePtr kthToLast(ForwardList<T> &l, int k) {
  typename ForwardList<T>::NodePtr p1 = l.head;
  typename ForwardList<T>::NodePtr p2 = l.head;

  /* Move p1 k nodes into the list. */
  for (int i = 0; i < k; ++i) {
    if (p1 == nullptr)
      return nullptr; // Out of bounds
    p1 = p1->next;
  }

  /* Move them at the same pace. When p1 hits the end, p2 will be at the right
   * element . */
  while (p1 != nullptr) {
    p1 = p1->next;
    p2 = p2->next;
  }
  return p2;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(ReturnKthToLastTest, Trivial) {
  ForwardList<int> list({1, 2, 3, 4, 5, 6, 7, 8, 9});

  ForwardList<int>::NodePtr n = nthToLast<int>(list, 3);
  EXPECT_EQ(n->data, 7);

  n = kthToLast<int>(list, 3);
  EXPECT_EQ(n->data, 7);
}
