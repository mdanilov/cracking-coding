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
    int value = values[top_index];  // Get top
    values[top_index] = 0;          // Clear
    sizes[stack_num]--;             // Shrink

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

// Solution #2
// ------------------------------------------------------------------------------------------------
class MultiStack {
 public:
  MultiStack(int number_of_stacks, size_t default_size)
      : values(number_of_stacks * default_size) {
    /* Create metadata for all stacks */
    for (int i = 0; i < number_of_stacks; ++i) {
      info.push_back(StackInfo(default_size * i, default_size, *this));
    }
  }

  /* Push value onto stack num, shifting/expanding stacks as necessary. Throws
   * exception if all stacks are full. */
  void push(int stack_num, int value) {
    if (allStacksAreFull()) {
      throw std::runtime_error("All stacks are full");
    }

    /* If this stack is full, expand it. */
    StackInfo &stack = info[stack_num];
    if (stack.isFull()) {
      expand(stack_num);
    }

    /* Find the index of the top element in the array + 1, and increment the
     * stack pointer */
    stack.size++;
    values[stack.lastElementIndex()] = value;
  }

  /* Get top element of stack.*/
  int peek(int stack_num) {
    StackInfo &stack = info[stack_num];
    return values[stack.lastElementIndex()];
  }

  /* Remove value from stack. */
  int pop(int stack_num) {
    StackInfo &stack = info[stack_num];
    if (stack.isEmpty()) {
      throw std::runtime_error("Stack is empty");
    }

    /* Remove last elemen. */
    int value = values[stack.lastElementIndex()];
    values[stack.lastElementIndex()] = 0;  // Clear item
    stack.size--;                          // Shrink size
    return value;
  }

  /* Shift items in stack over by one element. If we have available capacity,
   * then we'll end up shrinking the stack by one element. If we don't have
   * available capacity, then we'll need to shift the next stack over too. */
  void shift(int stack_num) {
    StackInfo &stack = info[stack_num];

    /* If this stack is at its full capacity, then you need to move the next
     * stack over by one element. This stack can now claim the freed index. */
    if (stack.size >= stack.capacity) {
      int next_stack = (stack_num + 1) % info.size();
      shift(next_stack);
      stack.capacity++;  // claim index that next stack lost
    }

    /* Shift all elements in stack over by one. */
    int index = stack.lastCapacityIndex();
    while (stack.isWithinStackCapacity(index)) {
      values[index] = values[previousIndex(index)];
      index = previousIndex(index);
    }

    /* Adjust stack data. */
    values[stack.start] = 0;               // Clear item
    stack.start = nextIndex(stack.start);  // move start
    stack.capacity--;                      // Shrink capacity
  }

  /* Expand stack by shifting over other stacks */
  void expand(int stack_num) {
    shift((stack_num + 1) % info.size());
    info[stack_num].capacity++;
  }

  /* Returns the number of items actually present in stack. */
  int numberOfElements() {
    int size = 0;
    for (StackInfo sd : info) {
      size += sd.size;
    }
    return size;
  }

  /* Returns true is all the stacks are full. */
  bool allStacksAreFull() { return numberOfElements() == values.size(); }

 private:
  struct StackInfo {
    size_t start;
    size_t size = 0;
    size_t capacity;
    MultiStack &parent;

    /* StackInfo is a simple structure that holds a set of data about each
     * stack. It does not hold the actual items in the stack. We could have done
     * this with just a bunch of individual variables, but that's messy and
     * doesn't gain us much. */
    StackInfo(size_t start, size_t capacity, MultiStack &parent)
        : start(start), capacity(capacity), parent(parent) {}

    /* Check if an index on the full array is within the stack boundaries. The
     * stack can wrap around to the start of the array. */
    bool isWithinStackCapacity(int index) {
      /* If outside of bounds of array, return false. */
      if (index < 0 || index >= parent.values.size()) {
        return false;
      }

      /* If index wraps around, adjust it. */
      int contiguousIndex =
          index < start ? index + parent.values.size() : index;
      int end = start + capacity;
      return start <= contiguousIndex && contiguousIndex < end;
    }

    size_t lastElementIndex() { return parent.adjustIndex(start + size - 1); }

    size_t lastCapacityIndex() {
      return parent.adjustIndex(start + capacity - 1);
    }

    bool isFull() { return size == capacity; }
    bool isEmpty() { return size == 0; }
  };

  /* Adjust index to be within the range of 0 -> length - 1. */
  int adjustIndex(int index) {
    /* Mod operator can return neg values. For example, (-11 % 5) will
     * return -1, not 4. We actually want the value to be 4 (since we're
     * wrapping around the index). */
    int max = values.size();
    return index > 0 ? index % max : (index % max) + max;
  }

  /* Get index after this index, adjusted for wrap around. */
  int nextIndex(int index) { return adjustIndex(index + 1); }

  /* Get index before this index, adjusted for wrap around. */
  int previousIndex(int index) { return adjustIndex(index - 1); }

  std::vector<StackInfo> info;
  std::vector<int> values;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(FreeInOneTest, Trivial) {
  {
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

  {
    MultiStack stack(3, 3);

    // normal case
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

    // shift case
    int expected_1 = 99;
    stack.push(0, expected_1);
    for (int i = 1; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        EXPECT_NO_THROW(stack.push(i, j));
      }
    }

    EXPECT_THROW(stack.push(0, 0), std::runtime_error);

    for (int i = 1; i < 3; ++i) {
      for (int expected = 3; expected >= 0; --expected) {
        int peeked = stack.peek(i);
        int popped = stack.pop(i);
        EXPECT_EQ(expected, peeked);
        EXPECT_EQ(expected, popped);
      }
    }

    int peeked = stack.peek(0);
    int popped = stack.pop(0);
    EXPECT_EQ(expected_1, peeked);
    EXPECT_EQ(expected_1, popped);

    EXPECT_THROW(stack.pop(0), std::runtime_error);
  }
}
