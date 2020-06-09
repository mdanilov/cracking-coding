#pragma once

#include <initializer_list>
#include <memory>

template <typename T> class ForwardList {
public:
  template <typename T1 = T> class Node {
  public:
    std::shared_ptr<Node<T1>> next = nullptr;
    T1 data;

    Node(T1 value) : data(value) {}
  };

  using NodePtr = std::shared_ptr<Node<T>>;

  ForwardList() {}

  ForwardList(std::initializer_list<T> l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
      appendToTail(*it);
    }
  }

  bool operator==(const ForwardList<T> &rhs) const {
    NodePtr n1 = head;
    NodePtr n2 = rhs.head;
    while (n1->next != nullptr && n2->next != nullptr) {
      if (n1->data != n2->data) {
        return false;
      }
      n1 = n1->next;
      n2 = n2->next;
    }
    return (n1->next == nullptr) && (n2->next == nullptr);
  }

  void appendToTail(T value) {
    NodePtr end = std::make_shared<Node<T>>(value);
    if (head == nullptr) {
      head = end;
      return;
    }

    NodePtr n = head;
    while (n->next != nullptr) {
      n = n->next;
    }
    n->next = end;
  }

  NodePtr head = nullptr;
};