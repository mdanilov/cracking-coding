# Stacks and Queues

1. A stack uses LIFO (last-in first-out) ordering. It uses the following operations:
  - pop(): Remove the top item from the stack.
  - push(item): Add an item to the top of the stack.
  - peek(): Return the top of the stack.
  - isEmpty(): Return true if and only if the stack is empty.

2. Unlike an array, a stack does not offer constant-time access to the ith item. However, it does allow constant-
time adds and removes.

3. One case where stacks are often useful is in certain recursive algorithms. A stack can also be used to implement a recursive algorithm iteratively.

4. A queue implements FIFO (first-in first-out) ordering. It uses the following operations:
  - add(item): Add an item to the end of the list.
  - remove(): Remove the first item in the list.
  - peek(): Return the top of the queue.
  - isEmpty(): Return true if and only ifthe queue is empty.

5. One place where queues are often used is in breadth-first search or in implementing a cache.
