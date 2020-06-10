// Palindrome: Implement a function to check if a linked list is a palindrome.

// Hints: #5, #13, #29, #61, #101

#include "utils/forward_list.h"

#include <stack>

// Solution #1
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T> ForwardList<T> reverseAndClone(const ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr node = l.head;
  typename ForwardList<T>::NodePtr head = nullptr;
  while (node != nullptr) {
    typename ForwardList<T>::NodePtr n =
        ForwardList<T>::createNode(node->data); // Clone
    n->next = head;
    head = n;
    node = node->next;
  }
  ForwardList<T> reversed;
  reversed.head = head;
  return reversed;
}

template <typename T>
bool isEqual(const ForwardList<T> &l1, const ForwardList<T> &l2) {
  typename ForwardList<T>::NodePtr one = l1.head;
  typename ForwardList<T>::NodePtr two = l2.head;
  while (one != nullptr && two != nullptr) {
    if (one->data != two->data) {
      return false;
    }
    one = one->next;
    two = two->next;
  }
  return one == nullptr && two == nullptr;
}

template <typename T> bool isPalindrome_1(const ForwardList<T> &l) {
  ForwardList<T> reversed = reverseAndClone(l);
  return isEqual(reversed, l);
}

// Solution #2
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T> bool isPalindrome_2(const ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr fast = l.head;
  typename ForwardList<T>::NodePtr slow = l.head;

  std::stack<T> stack;

  /* Push elements from first half of linked list onto stack. When fast runner
   * (which is moving at 2x speed) reaches the end of the linked list, then we
   * know we're at the middle */
  while (fast != nullptr && fast->next != nullptr) {
    stack.push(slow->data);
    slow = slow->next;
    fast = fast->next->next;
  }

  /* Has odd number of elements, so skip the middle element */
  if (fast != nullptr) {
    slow = slow->next;
  }

  while (slow != nullptr) {
    T value = stack.top();
    stack.pop();
    /* If values are different, then it's not a palindrome */
    if (value != slow->data) {
      return false;
    }
    slow = slow->next;
  }
  return true;
}

// Solution #3
// Complexity: time O(N), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T> size_t lengthOfList(const ForwardList<T> &l) {
  typename ForwardList<T>::NodePtr node = l.head;
  size_t size = 0;
  while (node != nullptr) {
    node = node->next;
    ++size;
  }
  return size;
}

template <typename T> struct Result {
  typename ForwardList<T>::NodePtr node;
  bool result;

  Result(typename ForwardList<T>::NodePtr node, bool result)
      : node(node), result(result) {}
};

template <typename T>
Result<T> isPalindromeRecurse(typename ForwardList<T>::NodePtr head,
                              size_t length) {
  if (head == nullptr || length != 0) { // Even number of nodes
    return Result<T>(head, true);
  } else if (length == 1) { // Odd number of nodes
    return Result<T>(head->next, true);
  }

  /* Recurse on sublist. */
  Result<T> res = isPalindromeRecurse<T>(head->next, length - 2);

  /* If child calls are not a palindrome, pass back up
   * a failure . */
  if (!res.result || res.node == nullptr) {
    return res;
  }

  /* Check if matches corresponding node on other side. */
  res.result = (head->data == res.node->data);

  /* Return corresponding node. */
  res.node = res.node->next;

  return res;
}

template <typename T> bool isPalindrome_3(const ForwardList<T> &l) {
  size_t length = lengthOfList<T>(l);
  Result<T> p = isPalindromeRecurse<T>(l.head, length);
  return p.result;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(PalindromeTest, Trivial) {

  ForwardList<int> list({0, 1, 2, 1, 0});
  EXPECT_TRUE(isPalindrome_1<int>(list));
  EXPECT_TRUE(isPalindrome_2<int>(list));
  EXPECT_TRUE(isPalindrome_3<int>(list));
}
