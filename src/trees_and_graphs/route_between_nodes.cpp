// Route Between Nodes: Given a directed graph, design an algorithm to find out
// whether there is a route between two nodes. Hints: #127

#include "utils/graph.h"
#include <list>

using namespace utils;

// Solution
// ------------------------------------------------------------------------------------------------
bool search(Graph &g, NodePtr start, NodePtr end) {
  if (start == end)
    return true;
  // operates as queue
  std::list<NodePtr> q;
  for (NodePtr u : g.getNodes()) {
    u->state = Node::State::kUnvisited;
  }
  start->state = Node::State::kVisiting;
  q.push_back(start);
  NodePtr u;
  while (!q.empty()) {
    u = q.front();
    q.pop_front(); // i.e. dequeue
    if (u != nullptr) {
      for (NodePtr v : u->getAdjacent()) {
        if (v->state == Node::State::kUnvisited) {
          if (v == end) {
            return true;
          } else {
            v->state = Node::State::kVisiting;
            q.push_back(v);
          }
        }
      }
      u->state = Node::State::kVisited;
    }
  }

  return false;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(RouteBetweenNodesTest, Trivial) {
  std::vector<Edge> edges = {{0, 1}, {1, 2}, {2, 0}, {2, 1},
                             {3, 2}, {4, 5}, {5, 4}};
  int N = 6;
  Graph g(edges, N);
  auto &nodes = g.getNodes();
  EXPECT_TRUE(search(g, nodes[5], nodes[4]));
  EXPECT_FALSE(search(g, nodes[5], nodes[1]));
  EXPECT_FALSE(search(g, nodes[1], nodes[3]));
  EXPECT_TRUE(search(g, nodes[3], nodes[0]));
  EXPECT_TRUE(search(g, nodes[1], nodes[0]));
  EXPECT_TRUE(search(g, nodes[0], nodes[0]));
}
