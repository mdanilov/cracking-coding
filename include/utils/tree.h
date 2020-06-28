#pragma once

#include <memory>

namespace utils {

struct TreeNode {
  int value;
  std::shared_ptr<TreeNode> left;
  std::shared_ptr<TreeNode> right;

  TreeNode(int v) : value(v) {}
};

using TreeNodePtr = std::shared_ptr<TreeNode>;

} // namespace utils
