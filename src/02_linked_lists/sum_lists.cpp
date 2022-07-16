// Sum Lists: You have two numbers represented by a linked list, where each node
// contains a single digit. The digits are stored in reverse order, such that
// the 1's digit is at the head of the list. Write a function that adds the two
// numbers and returns the sum as a linked list.
//
// EXAMPLE
// Input: (7 -> 1 -> 6) + (5 -> 9 -> 2).That is, 617 + 295.
// Output: 2 -> 1 -> 9. That is, 912.
//
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
//
// EXAMPLE
// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).That is, 617 + 295.
// Output: 9 -> 1 -> 2. That is, 912.

// Hints: #7, #30, #71, #95, #109

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T>
typename ForwardList<T>::NodePtr addLists(typename ForwardList<T>::NodePtr l1,
                                          typename ForwardList<T>::NodePtr l2,
                                          int carry) {
  if (l1 == nullptr && l2 == nullptr && carry == 0) {
    return nullptr;
  }

  typename ForwardList<T>::NodePtr result = ForwardList<T>::createNode();
  int value = carry;
  if (l1 != nullptr) {
    value += l1->data;
  }
  if (l2 != nullptr) {
    value += l2->data;
  }

  result->data = value % 10; /* Second digit of number */

  if (l1 != nullptr || l2 != nullptr) {
    typename ForwardList<T>::NodePtr more =
        addLists<T>(l1 == nullptr ? nullptr : l1->next,
                    l2 == nullptr ? nullptr : l2->next, value >= 10 ? 1 : 0);
    result->next = more;
  }

  return result;
}

template <typename T>
ForwardList<T> addLists_1(const ForwardList<T> &l1, const ForwardList<T> &l2) {
  int carry = 0;
  ForwardList<T> result;
  result.head = addLists<T>(l1.head, l2.head, carry);
  return result;
}

// Solution #2
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T>
size_t length(const ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr node = l.head;
  size_t size = 0;
  while (node != nullptr) {
    node = node->next;
    ++size;
  }
  return size;
}

/* Helper function to insert node in the front of a linked list */
template <typename T>
typename ForwardList<T>::NodePtr insertBefore(
    typename ForwardList<T>::NodePtr l, T data) {
  typename ForwardList<T>::NodePtr node = ForwardList<T>::createNode(data);
  if (l != nullptr) {
    node->next = l;
  }
  return node;
}

/* Pad the list with zeros */
template <typename T>
void padList(ForwardList<T> &l, int padding) {
  typename ForwardList<T>::NodePtr head = l.head;
  for (size_t i = 0; i < padding; ++i) {
    head = insertBefore<T>(head, 0);
  }
  l.head = head;
}
template <typename T>
struct PartialSum {
  typename ForwardList<T>::NodePtr sum = nullptr;
  T carry = 0;
};

template <typename T>
PartialSum<T> addListsHelper(typename ForwardList<T>::NodePtr l1,
                             typename ForwardList<T>::NodePtr l2) {
  if (l1 == nullptr && l2 == nullptr) {
    return PartialSum<T>();
  }
  /* Add smaller digits recursively */
  PartialSum<T> sum = addListsHelper<T>(l1->next, l2->next);
  /* Add carry to current data */
  T val = sum.carry + l1->data + l2->data;
  /* Insert sum of current digits */
  typename ForwardList<T>::NodePtr full_result =
      insertBefore<T>(sum.sum, val % 10);
  /* Return sum so far, and the carry value */
  sum.sum = full_result;
  sum.carry = val / 10;
  return sum;
}

template <typename T>
ForwardList<T> addLists_2(ForwardList<T> &l1, ForwardList<T> &l2) {
  size_t len1 = length<T>(l1);
  size_t len2 = length<T>(l2);

  /* Pad the shorter list with zeros */
  if (len1 < len2) {
    padList<T>(l1, len2 - len1);
  } else {
    padList<T>(l2, len1 - len2);
  }

  /* Add lists */
  PartialSum<T> sum = addListsHelper<T>(l1.head, l2.head);

  /* If there was a carry value left over, insert this at the front of the
   * list. Otherwise, just return the linked list. */
  ForwardList<T> result;
  if (sum.carry == 0) {
    result.head = sum.sum;
  } else {
    result.head = insertBefore<T>(sum.sum, sum.carry);
  }
  return result;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(SumListsTest, Trivial) {
  {
    ForwardList<int> list_1({7, 1, 6});
    ForwardList<int> list_2({5, 9, 2});
    ForwardList<int> expected_list({2, 1, 9});

    ForwardList<int> sum_list = addLists_1<int>(list_1, list_2);
    EXPECT_EQ(sum_list, expected_list);
  }

  {
    ForwardList<int> list_1({6, 1, 7});
    ForwardList<int> list_2({2, 9, 5});
    ForwardList<int> expected_list({9, 1, 2});

    ForwardList<int> sum_list = addLists_2<int>(list_1, list_2);
    EXPECT_EQ(sum_list, expected_list);
  }
}
