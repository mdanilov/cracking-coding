// Sort Stack: Write a program to sort a stack such that the smallest items are
// on the top. You can use an additional temporary stack, but you may not copy
// the elements into any other data structure (such as an array). The stack
// supports the following operations: push, pop, peek, and isEmpty.

#include <stack>

// Solution
// Complexity: time O(N^2), space O(N)
// ------------------------------------------------------------------------------------------------
template <typename T>
void sort(std::stack<T>& s) {
  std::stack<T> r;
  while (!s.empty()) {
    /* Insert each element in s in sorted order into r. */
    T tmp = s.top();
    s.pop();
    while (!r.empty() && r.top() > tmp) {
      s.push(r.top());
      r.pop();
    }
    r.push(tmp);
  }

  /* Copy the elements from r back into s. */
  s = std::move(r);
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(SortStackTest, Trivial) {
  std::stack<int> s({1, 5, 2, 4, 3});
  std::stack<int> sorted_s({1, 2, 3, 4, 5});
  sort(s);
  EXPECT_EQ(sorted_s, s);
}
