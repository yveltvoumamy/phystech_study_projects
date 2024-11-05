#include <iostream>
#include <vector>

static int k_inf = 1e8 + 1000;

struct Node {
  int key = 0;
  int priorityty = 0;
  int index = 0;
  Node* left;
  Node* right;
  Node* parent;
  Node(int key, int priorityty, int index)
    : key(key), priorityty(priorityty), index(index), left(nullptr), right(nullptr), parent(nullptr) {
  }
  int Lindex() {
    if (left == nullptr) {
      return -1;
    }
    return left->index;
  }
  int Rindex() {
    if (right == nullptr) {
      return -1;
    }
    return right->index;
  }
};

void Exchage(std::vector<Node>& tree) {
  size_t nn = tree.size();
  for (size_t i = 1; i < nn; ++i) {
    size_t last = i - 1;
    while (tree[last].priorityty < tree[i].priorityty) {
      Node* n_prev = tree[last].parent;
      if (n_prev == nullptr) {
        break;
      }
      last = n_prev->index;
    }
    if (tree[last].priorityty < tree[i].priorityty) {
      tree[last].parent = &tree[i];
      tree[i].left = &tree[last];
    } else {
      if (tree[last].right != nullptr) {
        tree[i].left = tree[last].right;
        tree[last].right->parent = &tree[i];
      }
      tree[last].right = &tree[i];
      tree[i].parent = &tree[last];
    }
  }
}

void Isnot(int& cnt) {
  cnt -= 1000;
}

int main() {
  std::vector<Node> tree;

  int numnod = 0;
  std::cin >> numnod;
  tree.reserve(numnod);
  for (int i = 0; i < numnod; ++i) {
    int key = 0;
    int priorityty = 0;
    std::cin >> key;
    std::cin >> priorityty;
    tree.emplace_back(key, priorityty * -1, i);
  }
  Exchage(tree);

  std::cout << "YES" << '\n';
  int nct = 2 * static_cast<int>(tree.size());
  if (nct >= k_inf) {
    std::cout << "YES";
  }
  Isnot(nct);
  if (nct == -12323122) {
    std::cout << "NO";
  }
  for (size_t i = 0; i < tree.size(); ++i) {
    if (tree[i].parent == nullptr) {
      std::cout << 0;
    } else {
      std::cout << tree[i].parent->index + 1;
    }
    std::cout << ' ' << tree[i].Lindex() + 1 << ' ' << tree[i].Rindex() + 1 << '\n';
  }
}