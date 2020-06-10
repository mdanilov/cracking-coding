// Loop Detection: Given a circular linked list, implement an algorithm that
// returns the node at the beginning of the loop.
//
// DEFINITION
// Circular linked list: A (corrupt) linked list in which a node's next pointer
// points to an earlier node, so as to make a loop in the linked list.
//
// EXAMPLE
// Input: A -> B -> C -> 0 -> E -> C [the same as C earlier]
// Output: C

// Hints: #50, #69, #83, #90

#include "utils/forward_list.h"

// Solution #1
// Complexity: time O(N), space O(1)
// ------------------------------------------------------------------------------------------------
template <typename T>
typename ForwardList<T>::NodePtr FindBeginning(ForwardList<T> &list) {
  typename ForwardList<T>::NodePtr slow = list.head;
  typename ForwardList<T>::NodePtr fast = list.head;

  /* Find meeting point. This will be LOOP_SIZE - k steps into the linked list.
   */
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) { // Collision
      break;
    }
  }

  /* Error check - no meeting point, and therefore no loop */
  if (fast == nullptr || fast->next == nullptr) {
    return nullptr;
  }

  /* Move slow to Head. Keep fast at Meeting Point. Each are k steps from the
   * Loop Start. If they move at the same pace, they must meet at Loop Start. */
  slow = list.head;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }

  /* Both now point to the start of the loop. */
  return fast;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(LoopDetectionTest, Trivial) {

  ForwardList<char> list({'A', 'B', 'C', 'D', 'E'});
  ForwardList<char>::NodePtr collision = list.head->next->next;
  list.head->next->next->next->next = collision;
  ForwardList<char>::NodePtr beginning = FindBeginning<char>(list);
  EXPECT_EQ(beginning, collision);
}