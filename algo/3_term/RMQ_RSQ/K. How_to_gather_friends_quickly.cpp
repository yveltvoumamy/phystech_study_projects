#include <iostream>
#include <random>

std::mt19937 rng(0);

struct Node {
  int64_t key;
  unsigned int priority;
  int64_t sum;

  Node *left, *right;

  explicit Node(int64_t key) : key(key), priority(rng()), sum(key), left(nullptr), right(nullptr) {
  }
};

class Treap {
public:
  Treap() : root_(nullptr) {
  }

  void Add(int64_t value);

  int64_t Get(int64_t left, int64_t right);

  ~Treap() {
    Clear(root_);
  }

private:
  Node* Merge(Node* left, Node* right);

  std::pair<Node*, Node*> Split(Node* root, int64_t key);

  void Recalc(Node* node);

  int64_t GetSum(Node* node);

  void Clear(Node* current);

  Node* root_;
};

Node* Treap::Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  if (left->priority > right->priority) {
    left->right = Merge(left->right, right);
    Recalc(left);
    return left;
  }
  right->left = Merge(left, right->left);
  Recalc(right);
  return right;
}

std::pair<Node*, Node*> Treap::Split(Node* root, int64_t key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->key < key) {
    auto [left, right] = Split(root->right, key);
    root->right = left;
    Recalc(root);
    return {root, right};
  }
  auto [left, right] = Split(root->left, key);
  root->left = right;
  Recalc(root);
  return {left, root};
}

void Treap::Add(int64_t value) {
  auto current = root_;
  while (current != nullptr) {
    if (current->key == value) {
      return;
    }
    if (current->key < value) {
      current = current->right;
    } else {
      current = current->left;
    }
  }
  auto [left, right] = Split(root_, value);
  root_ = Merge(Merge(left, new Node(value)), right);
}

int64_t Treap::Get(int64_t left, int64_t right) {
  auto [tl, tr] = Split(root_, left);
  auto [ql, qr] = Split(tr, right + 1);
  int64_t answer = GetSum(ql);
  root_ = Merge(tl, Merge(ql, qr));
  return answer;
}

int64_t Treap::GetSum(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->sum;
}

void Treap::Recalc(Node* node) {
  if (node == nullptr) {
    return;
  }
  node->sum = GetSum(node->left) + GetSum(node->right) + node->key;
}

void Treap::Clear(Node* current) {
  if (current == nullptr) {
    return;
  }
  Clear(current->left);
  Clear(current->right);
  delete current;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int query = 0;
  std::cin >> query;
  Treap tree;
  while (query-- > 0) {
    char type = 'a';
    std::cin >> type;
    if (type == '+') {
      int64_t val = 0;
      std::cin >> val;
      tree.Add(val);
    } else {
      int64_t left = 0;
      int64_t right = 0;
      std::cin >> left >> right;
      std::cout << tree.Get(left, right) << '\n';
    }
  }
}