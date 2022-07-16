// Remove Dups: Write code to remove duplicates from an unsorted linked list.
//
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

// Hints: #9, #40

#include <unordered_set>

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T>
void deleteDups_1(ForwardList<T> &l) {
  std::unordered_set<T> set;
  typename ForwardList<T>::NodePtr n = l.head;
  typename ForwardList<T>::NodePtr previous = nullptr;
  while (n != nullptr) {
    auto result = set.insert(n->data);
    if (result.second) {
      previous = n;
    } else {
      previous->next = n->next;
    }
    n = n->next;
  }
}

// Solution #2
// Complexity: time O(N^2), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T>
void deleteDups_2(ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr current = l.head;
  while (current != nullptr) {
    /* Remove all future nodes that have the same value */
    typename ForwardList<T>::NodePtr runner = current;
    while (runner->next != nullptr) {
      if (runner->next->data == current->data) {
        runner->next = runner->next->next;
      } else {
        runner = runner->next;
      }
    }
    current = current->next;
  }
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RemoveDupsTest, Trivial) {
  std::initializer_list<int> init_values({1, 2, 3, 4, 2, 3, 6, 7, 1, 9, 9});
  ForwardList<int> expected_list({1, 2, 3, 4, 6, 7, 9});

  {
    ForwardList<int> list(init_values);
    deleteDups_1(list);
    EXPECT_EQ(list, expected_list);
  }

  {
    ForwardList<int> list(init_values);
    deleteDups_2(list);
    EXPECT_EQ(list, expected_list);
  }
}
