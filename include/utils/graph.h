#pragma once

#include <cassert>
#include <memory>
#include <vector>

namespace utils {

class Node;

using NodePtr = std::shared_ptr<Node>;

class Node {
 public:
  enum class State { kUnvisited, kVisited, kVisiting };

  Node(int index) : index(index), state(State::kUnvisited) {}

  std::vector<NodePtr> &getAdjacent() { return nodes; }

  State state;

 private:
  int index;
  std::vector<NodePtr> nodes;
};

struct Edge {
  int src;
  int dst;
};

class Graph {
 public:
  Graph(const std::vector<Edge> &edges, int N) {
    nodes.resize(N);
    for (int i = 0; i < N; ++i) {
      nodes[i] = std::make_shared<Node>(i);
    }

    for (auto &edge : edges) {
      assert(edge.src < N);
      assert(edge.dst < N);
      nodes[edge.src]->getAdjacent().push_back(nodes[edge.dst]);
    }
  }

  std::vector<NodePtr> &getNodes() { return nodes; }

 private:
  std::vector<NodePtr> nodes;
};

}  // namespace utils
