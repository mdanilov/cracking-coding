// Queue via Stacks: Implement a MyQueue class which implements a queue using
// two stacks.

#include <cstddef>
#include <stack>

// Solution
// ------------------------------------------------------------------------------------------------
template <typename T>
class MyQueue {
 public:
  size_t size() { return stackNewest.size() + stackOldest.size(); }

  void add(T value) {
    /* Push onto stackNewest, which always has the newest elements on top */
    stackNewest.push(value);
  }

  T peek() {
    shiftStacks();             // Ensure stackOldest has the current elements
    return stackOldest.top();  // retrieve the oldest item.
  }

  T remove() {
    shiftStacks();  // Ensure stackOldest has the current elements
    T value = stackOldest.top();
    stackOldest.pop();  // pop the oldest item.
    return value;
  }

 private:
  void shiftStacks() {
    if (stackOldest.empty()) {
      while (!stackNewest.empty()) {
        stackOldest.push(stackNewest.top());
        stackNewest.pop();
      }
    }
  }

  std::stack<T> stackNewest;
  std::stack<T> stackOldest;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(QueueViaStacksTest, Trivial) {
  MyQueue<int> q;
  q.add(1);  // 1 ->
  q.add(2);  // 2 -> 1
  q.add(3);  // 3 -> 2 1
  EXPECT_EQ(1, q.peek());
  q.add(4);  // 4 -> 3 2 1
  EXPECT_EQ(1, q.peek());
  q.add(5);  // 5 -> 4 3 2 1
  EXPECT_EQ(5, q.size());
  EXPECT_EQ(1, q.remove());  // 5 4 3 2 -> 1
  EXPECT_EQ(4, q.size());
  EXPECT_EQ(2, q.remove());  // 5 4 3 -> 2
}
