#include <iostream>

struct Node {
  Node* prnt = nullptr;
  Node* l_son = nullptr;
  Node* r_son = nullptr;
  int64_t value = 0;
};

struct BinTreeOfSearch {
  Node* rt = nullptr;
};

void FastInputOutput();
void Input(int64_t& value, BinTreeOfSearch& tree);
void Insert(BinTreeOfSearch& tree, int64_t value);
void Clear(Node* node);
void DeleteLeaf(BinTreeOfSearch& tree, Node* node);
void Switch(BinTreeOfSearch& tree, Node* a, Node* b);
void Check(BinTreeOfSearch& tree, Node* a, Node* b);
int64_t SecondMax(BinTreeOfSearch& tree);
Node* Max(Node* node);
Node* Min(Node* node);

int main() {
  FastInputOutput();
  BinTreeOfSearch tree;
  int64_t value = 0;
  Input(value, tree);
  std::cout << SecondMax(tree) << '\n';
  Clear(tree.rt);
}

void Input(int64_t& value, BinTreeOfSearch& tree) {
  std::cin >> value;
  while (value != 0) {
    Insert(tree, value);
    std::cin >> value;
  }
}

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

Node* Min(Node* node) {
  if (node->l_son == nullptr) {
    return node;
  }
  return Min(node->l_son);
}

Node* Max(Node* node) {
  if (node->r_son == nullptr) {
    return node;
  }
  return Max(node->r_son);
}

int64_t SecondMax(BinTreeOfSearch& tree) {
  DeleteLeaf(tree, Max(tree.rt));
  return Max(tree.rt)->value;
}

void Insert(BinTreeOfSearch& tree, int64_t value) {
  auto* new_node = new Node;
  Node* b = nullptr;
  int is_same = 0;
  new_node->value = value;
  for (Node* a = tree.rt; a != nullptr;) {
    if (a->value == new_node->value) {
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
  if (is_same == 1) {
    delete new_node;
  } else {
    if (b != nullptr) {
      new_node->prnt = b;
      if (new_node->value < b->value) {
        b->l_son = new_node;
      } else {
        b->r_son = new_node;
      }
    } else {
      tree.rt = new_node;
    }
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

void Switch(BinTreeOfSearch& tree, Node* a, Node* b) {
  Check(tree, a, b);
  if (b != nullptr) {
    b->prnt = a->prnt;
  }
  delete a;
}

void Check(BinTreeOfSearch& tree, Node* a, Node* b) {
  if (a->prnt == nullptr) {
    tree.rt = b;
    return;
  }
  if (a->prnt->l_son == a) {
    a->prnt->l_son = b;
    return;
  }
  a->prnt->r_son = b;
}

void DeleteLeaf(BinTreeOfSearch& tree, Node* node) {
  if (node->l_son == nullptr) {
    Switch(tree, node, node->r_son);
    return;
  }
  if (node->r_son == nullptr) {
    Switch(tree, node, node->l_son);
    return;
  }
  Node* x = Min(node->r_son);
  if (x->prnt != node) {
    Switch(tree, x, x->r_son);
    x->r_son = node->r_son;
    x->r_son->prnt = x;
  }
  Switch(tree, node, x);
  x->l_son = node->l_son;
  x->l_son->prnt = x;
}
