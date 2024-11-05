#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct Node {
  T value;
  int prior = 0;
  int min = 0;
  size_t size = 1;
  Node* left = nullptr;
  Node* right = nullptr;

  Node(int64_t prior, const T& value) : value(value), prior(static_cast<int>(prior)) {
  }

  size_t LSize() {
    if (left == nullptr) {
      return 0;
    }
    return left->size;
  }

  size_t RSize() {
    if (right == nullptr) {
      return 0;
    }
    return right->size;
  }

  int Lmin() {
    if (left == nullptr) {
      return INT_MAX;
    }
    return left->min;
  }

  int Rmin() {
    if (right == nullptr) {
      return INT_MAX;
    }
    return right->min;
  }

  void Upd() {
    size = 1 + LSize() + RSize();
    min = std::min({Lmin(), Rmin(), value});
  }
  void Lchild(Node* child) {
    left = child;
  }

  void Rchild(Node* child) {
    right = child;
  }
};

template <typename T>
void Clear(Node<T>* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename T>
class Treap {
private:
  void Upd(Node<T>* node) {
    if (node != nullptr) {
      node->Upd();
    }
  }
  std::pair<Node<T>*, Node<T>*> Split(Node<T>* node, int cnt) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    int left_size = node->LSize();
    if (cnt <= left_size) {
      std::pair<Node<T>*, Node<T>*> pair = Split(node->left, cnt);
      node->Lchild(pair.second);
      Upd(node);
      return {pair.first, node};
    }
    std::pair<Node<T>*, Node<T>*> pair = Split(node->right, cnt - left_size - 1);
    node->Rchild(pair.first);
    Upd(node);
    return {node, pair.second};
  }
  Node<T>* Merge(Node<T>* first, Node<T>* second) {
    if (first == nullptr) {
      Upd(second);
      return second;
    }
    if (second == nullptr) {
      Upd(first);
      return first;
    }
    if (first->prior > second->prior) {
      first->Rchild(Merge(first->right, second));
      Upd(first->right);
      Upd(first);
      return first;
    }
    second->Lchild(Merge(first, second->left));
    Upd(second->left);
    Upd(second);
    return second;
  }
  std::pair<Node<T>*, Node<T>*> Find(Node<T>* parent, Node<T>* node, size_t pos) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    size_t left_size = node->LSize();
    if (pos == left_size) {
      return {parent, node};
    }
    if (pos < left_size) {
      return Find(node, node->left, pos);
    }
    return Find(node, node->right, pos - left_size - 1);
  }

public:
  void Insert(size_t pos, const T& value) {
    int prior = rand();
    auto node = new Node<T>(prior, value);
    std::pair<Node<T>*, Node<T>*> pair = Split(root, pos);
    root = Merge(Merge(pair.first, node), pair.second);
    Upd(root);
  }
  Node<T>* Find(int key) {
    return Find(nullptr, root, key).second;
  }
  int Min(size_t left, size_t right) {
    std::pair<Node<T>*, Node<T>*> pair_first = Split(root, right);
    std::pair<Node<T>*, Node<T>*> pair_second = Split(pair_first.first, left);
    int min = pair_second.second->min;
    root = Merge(Merge(pair_second.first, pair_second.second), pair_first.second);
    return min;
  }
  Treap() = default;

  ~Treap() {
    Clear(root);
  }

  void InOrder(Node<T>* node) {
    if (node == nullptr) {
      return;
    }
    if (!(node->left == nullptr)) {
      InOrder(node->left);
    }
    std::cout << node->key << ' ';
    if (node->right != nullptr) {
      InOrder(node->right);
    }
  }
  Node<T>* root = nullptr;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Treap<int> tree;
  size_t cnt = 0;
  std::cin >> cnt;
  for (size_t i = 0; i < cnt; ++i) {
    char type = 'a';
    std::cin >> type;
    if (type == '+') {
      size_t pos = 0;
      int value = 0;
      std::cin >> pos >> value;
      if (pos == 0) {
        tree.Insert(0, value);
      } else {
        tree.Insert(pos, value);
      }
    } else if (type == '?') {
      size_t left = 0;
      size_t right = 0;
      std::cin >> left >> right;
      std::cout << tree.Min(left - 1, right) << std::endl;
    }
  }
}
