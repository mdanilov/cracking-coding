// Partition: Write code to partition a linked list around a value x, such that
// all nodes less than x come before all nodes greater than or equal to x. lf x
// is contained within the list, the values of x only need to be after the
// elements less than x (see below). The partition element x can appear anywhere
// in the "right partition"; it does not need to appear between the left and
// right partitions.
//
// EXAMPLE
// Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
// Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8

// Hints: #3, #24

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(1), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T> void partition_1(ForwardList<T> &l, T x) {
  typename ForwardList<T>::NodePtr beforeStart = nullptr;
  typename ForwardList<T>::NodePtr beforeEnd = nullptr;
  typename ForwardList<T>::NodePtr afterStart = nullptr;
  typename ForwardList<T>::NodePtr afterEnd = nullptr;

  /* Partition list */
  typename ForwardList<T>::NodePtr node = l.head;
  while (node != nullptr) {
    typename ForwardList<T>::NodePtr next = node->next;
    node->next = nullptr;
    if (node->data < x) {
      /* Insert node into end of before list */
      if (beforeStart == nullptr) {
        beforeStart = node;
        beforeEnd = beforeStart;
      } else {
        beforeEnd->next = node;
        beforeEnd = node;
      }
    } else {
      /* Insert node into end of after list */
      if (afterStart == nullptr) {
        afterStart = node;
        afterEnd = afterStart;
      } else {
        afterEnd->next = node;
        afterEnd = node;
      }
    }
    node = next;
  }

  if (beforeStart == nullptr) {
    l.head = afterStart;
  } else {
    /* Merge before list and after list */
    beforeEnd->next = afterStart;
    l.head = beforeStart;
  }
}

// Solution #2
// Complexity: time O(1), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T> void partition_2(ForwardList<T> &l, T x) {
  typename ForwardList<T>::NodePtr node = l.head;

  typename ForwardList<T>::NodePtr head = node;
  typename ForwardList<T>::NodePtr tail = node;

  while (node != nullptr) {
    typename ForwardList<T>::NodePtr next = node->next;
    if (node->data < x) {
      /* Insert node at head.*/
      node->next = head;
      head = node;
    } else {
      /* Insert node at tail.*/
      tail->next = node;
      tail = node;
    }
    node = next;
  }
  tail->next = nullptr;

  // The head has changed, so we need to update it.
  l.head = head;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(PartitionTest, Trivial) {
  {
    ForwardList<int> list({3, 5, 8, 5, 10, 2, 1});
    ForwardList<int> expected_list({3, 2, 1, 5, 8, 5, 10});

    partition_1<int>(list, 5);
    EXPECT_EQ(list, expected_list);
  }

  {
    ForwardList<int> list({3, 5, 8, 5, 10, 2, 1});
    ForwardList<int> expected_list({1, 2, 3, 5, 8, 5, 10});

    partition_2<int>(list, 5);
    EXPECT_EQ(list, expected_list);
  }
}
