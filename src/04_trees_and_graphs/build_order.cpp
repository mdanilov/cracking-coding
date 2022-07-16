// Build Order: You are given a list of projects and a list of dependencies
// (which is a list of pairs of projects, where the second project is dependent
// on the first project). All of a project's dependencies must be built before
// the project is. Find a build order that will allow the projects to be built.
// If there is no valid build order, return an error.
//
// EXAMPLE
// Input:
//    projects: a, b, c, d, e, f
//    dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
// Output: f, e, a, b, d, c
//
// Hints: #26, #47, #60, #85, #125, #133

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

// Solution #1
// Complexity time O(P + D)
// ------------------------------------------------------------------------------------------------
class Project {
 public:
  enum class State { kBlank, kPartial, kComplete };

  Project(const std::string &n) : name(n) {}

  void addNeighbor(std::shared_ptr<Project> node) {
    auto is_added = map.insert({node->getName(), node}).second;
    if (is_added) {
      children.push_back(node);
      node->incrementDependencies();
    }
  }

  void incrementDependencies() { dependencies++; }
  void decrementDependencies() { dependencies--; }
  int getNumberDependencies() const { return dependencies; }

  void setState(State st) { state = st; }
  State getState() const { return state; }

  const std::string &getName() const { return name; }
  const std::vector<std::shared_ptr<Project>> &getChildren() const {
    return children;
  }

 private:
  std::string name;
  State state = State::kBlank;
  int dependencies = 0;
  std::vector<std::shared_ptr<Project>> children;
  std::unordered_map<std::string, std::shared_ptr<Project>> map;
};

class Graph {
 public:
  std::shared_ptr<Project> getOrCreateNode(const std::string &name) {
    if (map.find(name) == map.end()) {
      auto node = std::make_shared<Project>(name);
      nodes.push_back(node);
      map[name] = node;
    }
    return map[name];
  }

  void addEdge(const std::string &start_name, const std::string &end_name) {
    auto start = getOrCreateNode(start_name);
    auto end = getOrCreateNode(end_name);
    start->addNeighbor(end);
  }

  const std::vector<std::shared_ptr<Project>> &getNodes() const {
    return nodes;
  }

 private:
  std::vector<std::shared_ptr<Project>> nodes;
  std::unordered_map<std::string, std::shared_ptr<Project>> map;
};

/* Build the graph, adding the edge (a, b) if b is dependent on a. Assumes a
 * pair is listed in "build order". The pair (a , b) in dependencies indicates
 * that b depends on a and a must be built before b. */
using Dependency = std::pair<std::string, std::string>;
Graph buildGraph(const std::vector<std::string> &projects,
                 const std::vector<Dependency> &dependencies) {
  Graph graph;
  for (auto project : projects) {
    graph.getOrCreateNode(project);
  }

  for (auto dependency : dependencies) {
    graph.addEdge(dependency.first, dependency.second);
  }

  return graph;
}

/* A helper function to insert projects with zero dependencies into the order
 * array, starting at index offset. */
int addNonDependent(std::vector<std::shared_ptr<Project>> &order,
                    const std::vector<std::shared_ptr<Project>> &projects,
                    int offset) {
  for (auto project : projects) {
    if (project->getNumberDependencies() == 0) {
      order[offset] = project;
      offset++;
    }
  }
  return offset;
}

/* Return a list of the projects a correct build order. */
std::vector<std::shared_ptr<Project>> orderProjects_1(
    const std::vector<std::shared_ptr<Project>> &projects) {
  std::vector<std::shared_ptr<Project>> order(projects.size());

  /* Add "roots" to the build order first. */
  int end_of_list = addNonDependent(order, projects, 0);

  int to_be_processed = 0;
  while (to_be_processed < order.size()) {
    auto current = order[to_be_processed];

    /* We have a circular dependency since there are no remaining projects with
     * zero dependencies . */
    if (current == nullptr) {
      return order;
    }

    /* Remove myself as a dependency. */
    auto children = current->getChildren();
    for (auto child : children) {
      child->decrementDependencies();
    }

    /* Add children that have no one depending on them. */
    end_of_list = addNonDependent(order, children, end_of_list);
    to_be_processed++;
  }

  return order;
}

/* Find a correct build order. */
std::vector<std::shared_ptr<Project>> findBuildOrder_1(
    const std::vector<std::string> &projects,
    const std::vector<Dependency> &dependencies) {
  Graph graph = buildGraph(projects, dependencies);
  return orderProjects_1(graph.getNodes());
}

// Solution #2
// Complexity time O(P + D)
// ------------------------------------------------------------------------------------------------
bool doDFS(std::shared_ptr<Project> project,
           std::stack<std::shared_ptr<Project>> &stack) {
  if (project->getState() == Project::State::kPartial) {
    return false;  // Cycle
  }

  if (project->getState() == Project::State::kBlank) {
    project->setState(Project::State::kPartial);
    auto children = project->getChildren();
    for (auto child : children) {
      if (!doDFS(child, stack)) {
        return false;
      }
    }
    project->setState(Project::State::kComplete);
    stack.push(project);
  }

  return true;
}

std::stack<std::shared_ptr<Project>> orderProjects_2(
    const std::vector<std::shared_ptr<Project>> &projects) {
  std::stack<std::shared_ptr<Project>> stack;
  for (auto project : projects) {
    if (project->getState() == Project::State::kBlank) {
      if (!doDFS(project, stack)) {
        return stack;
      }
    }
  }

  return stack;
}

std::stack<std::shared_ptr<Project>> findBuildOrder_2(
    const std::vector<std::string> &projects,
    const std::vector<Dependency> &dependencies) {
  Graph graph = buildGraph(projects, dependencies);
  return orderProjects_2(graph.getNodes());
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(BuildOrderTest, Trivial) {
  {
    std::vector<std::string> expected_order = {"f", "d", "c", "b",
                                               "g", "a", "h", "e"};
    auto order = findBuildOrder_1({"f", "c", "b", "a", "h", "e", "d", "g"},
                                  {{"f", "c"},
                                   {"f", "b"},
                                   {"c", "a"},
                                   {"b", "a"},
                                   {"b", "h"},
                                   {"a", "e"},
                                   {"b", "e"},
                                   {"d", "g"}});
    EXPECT_EQ(expected_order.size(), order.size());
    for (size_t i = 0; i < order.size(); ++i) {
      EXPECT_EQ(expected_order[i], order[i]->getName());
    }
  }

  {
    std::vector<std::string> expected_order = {"d", "g", "f", "b",
                                               "h", "c", "a", "e"};
    auto order = findBuildOrder_2({"f", "c", "b", "a", "h", "e", "d", "g"},
                                  {{"f", "c"},
                                   {"f", "b"},
                                   {"c", "a"},
                                   {"b", "a"},
                                   {"b", "h"},
                                   {"a", "e"},
                                   {"b", "e"},
                                   {"d", "g"}});
    EXPECT_EQ(expected_order.size(), order.size());
    size_t i = 0;
    while (!order.empty()) {
      EXPECT_EQ(expected_order[i], order.top()->getName());
      ++i;
      order.pop();
    }
  }
}
