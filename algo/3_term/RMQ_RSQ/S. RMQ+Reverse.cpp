#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

const int kInf = 2 * 1e9;

template <typename T>
struct Node {
  T value;
  int64_t prior = 0;
  int min = 0;
  size_t size = 1;
  Node* left = nullptr;
  Node* right = nullptr;
  bool reversed = false;
  Node(int64_t prior, const T& value) : value(value), prior(prior), reversed(false) {
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
      return kInf;
    }
    return left->min;
  }
  int Rmin() {
    if (right == nullptr) {
      return kInf;
    }
    return right->min;
  }
  void Upd() {
    size = LSize() + RSize();
    size++;
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
struct Treap {
private:
  void Push(Node<T>* node) {
    if (node == nullptr) {
      return;
    }
    if (node->reversed) {
      std::swap(node->left, node->right);
      if (node->right != nullptr) {
        node->right->reversed ^= 1;
      }
      if (node->left != nullptr) {
        node->left->reversed ^= 1;
      }
    }
    node->reversed = false;
  }
  void Upd(Node<T>* node) {
    if (node != nullptr) {
      node->Upd();
    }
  }
  std::pair<Node<T>*, Node<T>*> Split(Node<T>* node, int cnt) {
    Push(node);
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
    Push(first);
    Push(second);
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
  std::pair<Node<T>*, Node<T>*> Find(Node<T>* parent, Node<T>* node, size_t pos) const {
    Push(node);
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
    std::pair<Node<T>*, Node<T>*> pairf = Split(root, right);
    std::pair<Node<T>*, Node<T>*> pairs = Split(pairf.first, left);
    int min = pairs.second->min;
    root = Merge(Merge(pairs.first, pairs.second), pairf.second);
    return min;
  }

  void Reverse(size_t left, size_t right) {
    std::pair<Node<T>*, Node<T>*> pairf = Split(root, right);
    std::pair<Node<T>*, Node<T>*> pairs = Split(pairf.first, left);
    pairs.second->reversed ^= 1;
    root = Merge(Merge(pairs.first, pairs.second), pairf.second);
  }

  explicit Treap(const std::vector<int>& array) {
    if (array.empty()) {
      return;
    }
    size_t i = array.size();
    do {
      --i;
      Insert(0, array[i]);
    } while (i != 0);
  }
  ~Treap() {
    Clear(root);
  }

  void InOrder(Node<T>* node) {
    if (!(node != nullptr)) {
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

  Treap() = default;
};

int main() {

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::vector<int> array;
  size_t cnt = 0;

  size_t size = 0;
  std::cin >> size >> cnt;
  array.resize(size);
  for (auto& el : array) {
    std::cin >> el;
  }

  Treap<int> tree(array);
  for (size_t i = 0; i < cnt; ++i) {
    size_t left = 0;
    size_t right = 0;
    char type = 'a';
    std::cin >> type >> left >> right;
    if (type == '1') {
      tree.Reverse(left - 1, right);
    } else if (type == '2') {
      std::cout << tree.Min(left - 1, right) << std::endl;
    } else {
      std::cout << "error";
    }
  }
}
