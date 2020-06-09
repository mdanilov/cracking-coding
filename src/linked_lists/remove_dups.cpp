// Remove Dups: Write code to remove duplicates from an unsorted linked list.
//
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

// Hints: #9, #40

#include "utils/forward_list.h"

#include <unordered_set>

// Solution #1
// ------------------------------------------------------------------------------------------------
template <typename T> void deleteDups(ForwardList<T> &l) {
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

// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RemoveDups, Trivial) {
  ForwardList<int> list({1, 2, 3, 4, 2, 3, 6, 7, 1, 9, 9});
  deleteDups(list);
  ForwardList<int> expected_list({1, 2, 3, 4, 6, 7, 9});
  EXPECT_EQ(list, expected_list);
}
