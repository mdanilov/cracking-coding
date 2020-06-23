// Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too
// high, it might topple. Therefore, in real life, we would likely start a new
// stack when the previous stack exceeds some threshold. Implement a data
// structure SetOfStacks that mimics this. SetOfStacks should be composed of
// several stacks and should create a new stack once the previous one exceeds
// capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically
// to a single stack (that is, pop() should return the same values as it would
// if there were just a single stack).

// FOLLOW UP
// Implement a function popAt (int index) which performs a pop operation on a
// specific sub-stack.

#include <memory>
#include <stdexcept>
#include <vector>

struct Node {
  int value;
  std::shared_ptr<Node> below;
  std::shared_ptr<Node> above;

  Node(int v) : value(v) {}
};

class Stack {
public:
  Stack(int capacity) : capacity(capacity) {}

  bool push(int v) {
    if (size >= capacity)
      return false;
    size++;
    std::shared_ptr<Node> n = std::make_shared<Node>(v);
    if (size == 1)
      bottom = n;
    join(n, top);
    top = n;
    return true;
  }

  int pop() {
    std::shared_ptr<Node> t = top;
    top = top->below;
    size--;
    return t->value;
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return capacity == size; }

  int removeBottom() {
    std::shared_ptr<Node> b = bottom;
    bottom = bottom->above;
    if (bottom != nullptr)
      bottom->below = nullptr;
    size--;
    return b->value;
  }

  int getSize() { return size; }

private:
  void join(std::shared_ptr<Node> above, std::shared_ptr<Node> below) {
    if (below != nullptr)
      below->above = above;
    if (above != nullptr)
      above->below = below;
  }

  int capacity;
  int size = 0;
  std::shared_ptr<Node> top;
  std::shared_ptr<Node> bottom;
};

class SetOfStacks {
public:
  SetOfStacks(int capacity) : capacity(capacity) {}

  void push(int v) {
    Stack *last = getLastStack();
    if (last != nullptr && !last->isFull()) { // add to last stack
      last->push(v);
    } else { // must create new stack
      Stack stack(capacity);
      stack.push(v);
      stacks.push_back(std::move(stack));
    }
  }

  bool isEmpty() {
    Stack *last = getLastStack();
    return last == nullptr || last->isEmpty();
  }

  int pop() {
    Stack *last = getLastStack();
    if (last == nullptr)
      throw std::runtime_error("Stack is empty");
    int v = last->pop();
    if (last->getSize() == 0)
      stacks.pop_back();
    return v;
  }

  int popAt(int index) { return leftShift(index, true); }

private:
  Stack *getLastStack() {
    if (stacks.size() == 0)
      return nullptr;
    return &stacks[stacks.size() - 1];
  }

  int leftShift(int index, bool removeTop) {
    Stack &stack = stacks[index];
    int removed_item;
    if (removeTop)
      removed_item = stack.pop();
    else
      removed_item = stack.removeBottom();
    if (stack.isEmpty()) {
      stacks.erase(stacks.begin() + index);
    } else if (stacks.size() > index + 1) {
      int v = leftShift(index + 1, false);
      stack.push(v);
    }
    return removed_item;
  }

  int capacity;
  std::vector<Stack> stacks;
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(StackOfPlatesTest, Trivial) {
  SetOfStacks s(3);
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.push(6);
  s.push(7);
  s.push(8);
  s.push(9);

  EXPECT_EQ(9, s.pop());    // 1 2 3 -> 4 5 6 -> 7 8 (9)
  EXPECT_EQ(3, s.popAt(0)); // 1 2 (3) -> 4 5 6 -> 7 8
  EXPECT_EQ(8, s.pop());    // 1 2 4 -> 5 6 7 -> (8)
  EXPECT_EQ(7, s.popAt(1)); // 1 2 4 -> 5 6 (7)
  EXPECT_EQ(4, s.popAt(0)); // 1 2 (4) -> 5 6
  EXPECT_EQ(6, s.pop());    // 1 2 5 -> (6)
  EXPECT_EQ(5, s.pop());    // 1 2 (5)
  EXPECT_EQ(2, s.pop());    // 1 (2)
  EXPECT_EQ(1, s.pop());    // (1)
  EXPECT_TRUE(s.isEmpty());
}
