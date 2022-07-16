// Stack Min: How would you design a stack which, in addition to push and pop,
// has a function min which returns the minimum element? Push, pop and min
// should all operate in 0(1) time.

#include <algorithm>
#include <limits>
#include <stack>

// Solution
// ------------------------------------------------------------------------------------------------
struct NodeWithMin {
  int value;
  int min;

  NodeWithMin(int v, int min) : value(v), min(min) {}
};

class StackWithMin {
 public:
  void push(int value) {
    int newMin = std::min(value, min());
    s.push(NodeWithMin(value, newMin));
  }

  int min() {
    if (s.empty()) {
      return std::numeric_limits<int>::max();  // Error value
    } else {
      return s.top().min;
    }
  }

  int pop() {
    NodeWithMin node = s.top();
    s.pop();
    return node.value;
  }

 private:
  std::stack<NodeWithMin> s;
};

// Solution #2
// ------------------------------------------------------------------------------------------------
class StackWithMin2 {
 public:
  void push(int value) {
    if (value <= min()) {
      s2.push(value);
    }
    s1.push(value);
  }

  int pop() {
    int value = s1.top();
    s1.pop();
    if (value == min()) {
      s2.pop();
    }
    return value;
  }

  int min() {
    if (s2.empty()) {
      return std::numeric_limits<int>::max();  // Error value
    } else {
      return s2.top();
    }
  }

 private:
  std::stack<int> s1;
  std::stack<int> s2;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(StackMinTest, Trivial) {
  {
    StackWithMin s;
    s.push(2);
    s.push(1);
    s.push(4);
    s.push(3);

    EXPECT_EQ(1, s.min());
    EXPECT_EQ(3, s.pop());
    EXPECT_EQ(1, s.min());
    EXPECT_EQ(4, s.pop());
    EXPECT_EQ(1, s.min());
    EXPECT_EQ(1, s.pop());
    EXPECT_EQ(2, s.min());
    EXPECT_EQ(2, s.pop());
    EXPECT_EQ(std::numeric_limits<int>::max(), s.min());
  }

  {
    StackWithMin2 s;
    s.push(2);
    s.push(1);
    s.push(4);
    s.push(3);

    EXPECT_EQ(1, s.min());
    EXPECT_EQ(3, s.pop());
    EXPECT_EQ(1, s.min());
    EXPECT_EQ(4, s.pop());
    EXPECT_EQ(1, s.min());
    EXPECT_EQ(1, s.pop());
    EXPECT_EQ(2, s.min());
    EXPECT_EQ(2, s.pop());
    EXPECT_EQ(std::numeric_limits<int>::max(), s.min());
  }
}
