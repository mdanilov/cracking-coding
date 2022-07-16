// Intersection: Given two (singly) linked lists, determine if the two lists
// intersect. Return the intersecting node. Note that the intersection is
// defined based on reference, not value. That is, if the kth node of the first
// linked list is the exact same node (by reference) as the jth node of the
// second linked list, then they are intersecting.

// Hints: #20, #45, #55, #65, #76, #93, #111, #120, #129

#include <cmath>

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(N), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T>
struct Result {
  typename ForwardList<T>::NodePtr tail;
  size_t size;

  Result(typename ForwardList<T>::NodePtr tail, size_t size)
      : tail(tail), size(size) {}
};

template <typename T>
Result<T> getTailAndSize(const ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr node = l.head;
  if (node == nullptr) return Result<T>(nullptr, 0);

  size_t size = 1;
  while (node->next != nullptr) {
    ++size;
    node = node->next;
  }

  return Result<T>(node, size);
}

template <typename T>
typename ForwardList<T>::NodePtr getKthNode(
    typename ForwardList<T>::NodePtr current, size_t k) {
  while (k > 0 && current != nullptr) {
    current = current->next;
    k--;
  }
  return current;
}

template <typename T>
typename ForwardList<T>::NodePtr findIntersection(ForwardList<T> &list1,
                                                  ForwardList<T> &list2) {
  if (list1.head == nullptr || list2.head == nullptr) return nullptr;

  /* Get tail and sizes */
  Result<T> result1 = getTailAndSize(list1);
  Result<T> result2 = getTailAndSize(list2);

  /* If different tail nodes, then there's no intersection. */
  if (result1.tail != result2.tail) {
    return nullptr;
  }

  /* Set pointers to the start of each linked list. */
  typename ForwardList<T>::NodePtr shorter =
      result1.size < result2.size ? list1.head : list2.head;
  typename ForwardList<T>::NodePtr longer =
      result1.size < result2.size ? list2.head : list1.head;

  /* Advance the pointer for the longer linked list by difference in lengths. */
  longer = getKthNode<T>(
      longer, std::abs(static_cast<int>(result1.size - result2.size)));

  /* Move both pointers until you have a collision. */
  while (shorter != longer) {
    shorter = shorter->next;
    longer = longer->next;
  }

  /* Return either one. */
  return longer;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(IntersectionTest, Trivial) {
  ForwardList<int> list_1({3, 1, 5, 9, 7, 2, 1});
  ForwardList<int> list_2({4, 6, 7, 2, 1});

  EXPECT_EQ(findIntersection<int>(list_1, list_2), nullptr);

  ForwardList<int>::NodePtr intersection = list_1.head->next->next->next->next;
  list_2.head->next->next = intersection;
  EXPECT_EQ(findIntersection<int>(list_1, list_2), intersection);
}
