#include <iostream>
#include <string>
#include <vector>

struct Node {
  int key = 0;
  int prior = 0;
  size_t size = 0;
  Node* left = nullptr;
  Node* right = nullptr;

  Node(int key, int prior) : key(key), prior(prior), size(1) {
  }

  size_t Lefts() {
    if (left == nullptr) {
      return 0;
    }
    return left->size;
  }

  size_t Rights() {
    if (right == nullptr) {
      return 0;
    }
    return right->size;
  }

  void CalcNew() {
    size = 1 + Lefts() + Rights();
  }

  void LChild(Node* child) {
    left = child;
  }

  void RChild(Node* child) {
    right = child;
  }
};

void Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->left);
  Clear(node->right);
  delete node;
}

class Deramida {
private:
  void CalcNew(Node* node) {
    if (node != nullptr) {
      node->CalcNew();
    }
  }
  std::pair<Node*, Node*> Split(Node* node, int key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key < node->key) {
      std::pair<Node*, Node*> pair = Split(node->left, key);
      node->LChild(pair.second);
      CalcNew(node);
      return {pair.first, node};
    }
    std::pair<Node*, Node*> pair = Split(node->right, key);
    node->RChild(pair.first);
    CalcNew(node);
    return {node, pair.second};
  }

  Node* Merge(Node* first, Node* second) {
    if (first == nullptr) {
      CalcNew(second);
      return second;
    }
    if (second == nullptr) {
      CalcNew(first);
      return first;
    }
    if (first->key > second->key) {
      std::swap(first, second);
    }
    if (first->prior > second->prior) {
      first->RChild(Merge(first->right, second));
      CalcNew(first->right);
      CalcNew(first);
      return first;
    }
    second->LChild(Merge(first, second->left));
    CalcNew(second->left);
    CalcNew(second);
    return second;
  }

  std::pair<Node*, Node*> Find(Node* parent, Node* node, int key) const {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (node->key == key) {
      return {parent, node};
    }
    if (key <= node->key) {
      return Find(node, node->left, key);
    }
    return Find(node, node->right, key);
  }

public:
  void Erase(int value) {
    if (Find(value) == nullptr) {
      return;
    }
    std::pair<Node*, Node*> pair_first = Split(root, value);
    std::pair<Node*, Node*> pair_second = Split(pair_first.first, value - 1);
    delete pair_second.second;
    root = Merge(pair_second.first, pair_first.second);
    CalcNew(root);
  }

  void Insert(int key) {
    if (Find(nullptr, root, key).second != nullptr) {
      return;
    }
    int prior = rand();
    Node* node = new Node(key, prior);
    std::pair<Node*, Node*> pair = Split(root, key);
    root = Merge(Merge(pair.first, node), pair.second);
    CalcNew(root);
  }

  Node* Next(Node* cur, int key) {
    if (cur == nullptr) {
      return nullptr;
    }
    if (cur->key <= key) {
      return Next(cur->right, key);
    }
    if (cur->left != nullptr) {
      Node* ans = Next(cur->left, key);
      if (ans == nullptr) {
        return cur;
      }
      return ans;
    }
    return cur;
  }

  Node* Prev(Node* cur, int key) {
    if (cur == nullptr) {
      return nullptr;
    }
    if (cur->key >= key) {
      return Prev(cur->left, key);
    }
    if (cur->right != nullptr) {
      Node* ans = Prev(cur->right, key);
      if (ans == nullptr) {
        return cur;
      }
      return ans;
    }
    return cur;
  }

  Node* OStat(Node* cur, size_t number) {
    if (!(cur != nullptr) or number > cur->size) {
      return nullptr;
    }
    if (!(cur->Lefts() + 1 != number)) {
      return cur;
    }
    if (number <= cur->Lefts()) {
      return OStat(cur->left, number);
    }
    return OStat(cur->right, number - cur->Lefts() - 1);
  }

  Node* Find(int key) {
    return Find(nullptr, root, key).second;
  }

  void MakeOrder(Node* node) {
    if (node == nullptr) {
      return;
    }
    if (node->left != nullptr) {
      MakeOrder(node->left);
    }
    std::cout << node->key << ' ';
    if (node->right != nullptr) {
      MakeOrder(node->right);
    }
  }

  Deramida() = default;

  ~Deramida() {
    Clear(root);
  }

  Node* root = nullptr;
};

void PrintAns(Node* node) {
  if (node == nullptr) {
    std::cout << "none" << '\n';
    return;
  }
  std::cout << node->key << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string operation;
  Deramida dertree;
  while (std::cin >> operation) {
    int value = 0;
    std::cin >> value;
    if (operation == "insert") {
      dertree.Insert(value);
    } else if (operation == "delete") {
      dertree.Erase(value);
    } else if (operation == "exists") {
      std::cout << ((dertree.Find(value) == nullptr) ? "false" : "true") << '\n';
    } else if (operation == "start") {
      std::cout << "begin";
    } else if (operation == "next") {
      PrintAns(dertree.Next(dertree.root, value));
    } else if (operation == "prev") {
      PrintAns(dertree.Prev(dertree.root, value));
    } else if (operation == "kth") {
      PrintAns(dertree.OStat(dertree.root, value + 1));
    } else {
      std::cout << "break";
    }
  }
}