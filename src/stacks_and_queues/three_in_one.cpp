// Three in One: Describe how you could use a single array to implement three
// stacks.

#include <stdexcept>
#include <vector>

// Solution #1
// ------------------------------------------------------------------------------------------------
class FixedMulitStack {
public:
  explicit FixedMulitStack(size_t stack_size)
      : values(stack_size * kNumberOfStacks), sizes(kNumberOfStacks) {
    stack_capacity = stack_size;
  }

  /* Push value onto stack. */
  void push(int stack_num, int value) {
    /* Check that we have space for the next element */
    if (isFull(stack_num)) {
      throw std::runtime_error("Stack is full");
    }

    /* Increment stack pointer and then update top value. */
    sizes[stack_num]++;
    values[indexOfTop(stack_num)] = value;
  }

  /* Pop item from top stack. */
  int pop(int stack_num) {
    if (isEmpty(stack_num)) {
      throw std::runtime_error("Stack is empty");
    }

    size_t top_index = indexOfTop(stack_num);
    int value = values[top_index]; // Get top
    values[top_index] = 0;         // Clear
    sizes[stack_num]--;            // Shrink

    return value;
  }

  /* Return top element. */
  int peek(int stack_num) {
    if (isEmpty(stack_num)) {
      throw std::runtime_error("Stack is empty");
    }
    return values[indexOfTop(stack_num)];
  }

  /* Return if stack is empty. */
  bool isEmpty(int stack_num) { return sizes[stack_num] == 0; }

  /* Return if stack is full. */
  bool isFull(int stack_num) { return sizes[stack_num] == stack_capacity; }

private:
  /* Returns index of the top of the stack. */
  int indexOfTop(int stack_num) {
    int offset = stack_num * stack_capacity;
    int size = sizes[stack_num];
    return offset + size - 1;
  }

  static const int kNumberOfStacks = 3;
  size_t stack_capacity;
  std::vector<int> values;
  std::vector<size_t> sizes;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(FreeInOneTest, Trivial) {
  FixedMulitStack stack(3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      stack.push(i, j);
    }
  }

  EXPECT_THROW(stack.push(0, 0), std::runtime_error);

  for (int i = 0; i < 3; ++i) {
    for (int expected = 2; expected >= 0; --expected) {
      int peeked = stack.peek(i);
      int popped = stack.pop(i);
      EXPECT_EQ(expected, peeked);
      EXPECT_EQ(expected, popped);
    }
  }

  EXPECT_THROW(stack.pop(0), std::runtime_error);
}
