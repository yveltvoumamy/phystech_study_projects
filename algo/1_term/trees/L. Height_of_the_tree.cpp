#include <iostream>

struct Node {
  Node* l_son = nullptr;
  Node* r_son = nullptr;
  int64_t value = 0;
};

struct BinTreeOfSearch {
  Node* rt = nullptr;
};

void FastInput();
void Input(int64_t& value, BinTreeOfSearch& tree);
void Insert(BinTreeOfSearch& tree, int64_t value);
void Clear(Node* node);
void Height(Node* node, int64_t& h, int64_t& tmp_h);
int64_t GetHeight(BinTreeOfSearch tree);

int main() {
  FastInput();
  BinTreeOfSearch tree;
  int64_t value = 0;
  Input(value, tree);
  std::cout << GetHeight(tree) << '\n';
  Clear(tree.rt);
}

void Input(int64_t& value, BinTreeOfSearch& tree) {
  std::cin >> value;
  while (value != 0) {
    Insert(tree, value);
    std::cin >> value;
  }
}

void FastInput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

void Insert(BinTreeOfSearch& tree, int64_t value) {
  Node* b = nullptr;
  auto* new_node = new Node;
  new_node->value = value;
  int is_same = 0;
  for (Node* a = tree.rt; a != nullptr;) {
    if (new_node->value == a->value) {
      is_same = 1;
      break;
    }
    b = a;
    if (a->value <= new_node->value) {
      a = a->r_son;
    } else {
      a = a->l_son;
    }
  }
  if (is_same == 0 && b != nullptr && b->value <= new_node->value) {
    b->r_son = new_node;
  } else if (is_same == 0 && b != nullptr && b->value > new_node->value) {
    b->l_son = new_node;
  } else if (b == nullptr && is_same == 0) {
    tree.rt = new_node;
  } else {
    delete new_node;
  }
}

int64_t GetHeight(BinTreeOfSearch tree) {
  int64_t tmp_h = 0;
  int64_t h = 0;
  Height(tree.rt, h, tmp_h);
  return h;
}

void Height(Node* node, int64_t& h, int64_t& tmp_h) {
  if (node == nullptr && tmp_h > h) {
    h = tmp_h;
    return;
  }
  if (node == nullptr) {
    return;
  }
  ++tmp_h;
  Height(node->l_son, h, tmp_h);
  Height(node->r_son, h, tmp_h);
  --tmp_h;
  if (tmp_h > h) {
    h = tmp_h;
  }
}

void Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->l_son);
  Clear(node->r_son);
  delete node;
}