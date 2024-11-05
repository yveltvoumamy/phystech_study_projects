#include <iostream>

struct Node {
  Node* prnt = nullptr;
  Node* l_son = nullptr;
  Node* r_son = nullptr;
  int64_t value = 0;
  int64_t height = 1;
};

struct AVL {
  Node* rt = nullptr;
};

void TargetSetting(AVL& avl_tree, char& command, char& prev_command, int64_t& x, int64_t& y);
int64_t Comparison(char command);
int64_t Height(Node* node);
void FixHeight(Node* node);
int64_t Max(int64_t a, int64_t b);
Node* LeftRotate(Node* node);
Node* RightRotate(Node* node);
int64_t BFactor(Node* node);
Node* Balance(Node* node);
Node* Add(AVL& avl_tree, Node* new_node);
int64_t Next(AVL& avl_tree, int64_t value);
void Clear(Node* node);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVL avl_tree;
  int n;
  int x;
  int y;
  char command;
  char prev_command;

  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> x;
      auto* new_node = new Node;
      if (prev_command == '?') {
        new_node->value = (x + y) % 1000000000;
      } else {
        new_node->value = x;
      }
      avl_tree.rt = Add(avl_tree, new_node);
      prev_command = '+';
    } else {
      prev_command = '?';
      std::cin >> x;
      y = Next(avl_tree, x);
      std::cout << y << '\n';
    }
  }
  Clear(avl_tree.rt);
  return 0;
}

void TargetSetting(AVL& avl_tree, char& command, char& prev_command, int64_t& x, int64_t& y) {
  switch (Comparison(command)) {
    case 0: {
      auto* new_node = new Node;
      std::cin >> x;
      if (prev_command == '+') {
        new_node->value = x;
      } else {
        new_node->value = (x + y) % 1000000000;
      }
      prev_command = '+';
      avl_tree.rt = Add(avl_tree, new_node);
    } break;
    case 1: {
      prev_command = '?';
      std::cin >> x;
      y = Next(avl_tree, x);
      std::cout << y << ' ';
    } break;
    case 404: {
      std::cout << "error\n";
    } break;
  }
}

int64_t Comparison(char command) {
  if (command == '?') {
    return 1;
  }
  if (command == '+') {
    return 0;
  }
  return 404;
}

int64_t Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int64_t Max(int64_t a, int64_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

void FixHeight(Node* node) {
  node->height = Max(Height(node->r_son) + 1, Height(node->l_son) + 1);
}

Node* LeftRotate(Node* node) {
  Node* new_node = node->r_son;
  new_node->prnt = node->prnt;
  if (node->prnt != nullptr) {
    if (node == node->prnt->l_son) {
      node->prnt->l_son = new_node;
    } else {
      node->prnt->r_son = new_node;
    }
  }
  node->r_son = new_node->l_son;
  if (new_node->l_son == nullptr) {
    new_node->l_son = node;
    node->prnt = new_node;
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }
  new_node->l_son->prnt = node;
  new_node->l_son = node;
  node->prnt = new_node;
  FixHeight(node);
  FixHeight(new_node);
  return new_node;
}

Node* RightRotate(Node* node) {
  Node* new_node = node->l_son;
  new_node->prnt = node->prnt;
  if (node->prnt != nullptr) {
    if (node == node->prnt->l_son) {
      node->prnt->l_son = new_node;
    } else {
      node->prnt->r_son = new_node;
    }
  }
  node->l_son = new_node->r_son;
  if (new_node->r_son == nullptr) {
    new_node->r_son = node;
    node->prnt = new_node;
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }
  new_node->r_son->prnt = node;
  new_node->r_son = node;
  node->prnt = new_node;
  FixHeight(node);
  FixHeight(new_node);
  return new_node;
}

int64_t BFactor(Node* node) {
  return Height(node->r_son) - Height(node->l_son);
}

Node* Balance(Node* node) {
  FixHeight(node);
  int64_t bfactor_node = BFactor(node);
  if (bfactor_node == 2) {
    if (BFactor(node->r_son) >= 0) {
      node = LeftRotate(node);
    } else {
      node->r_son = RightRotate(node->r_son);
      node = LeftRotate(node);
    }
  } else if (bfactor_node == -2) {
    if (BFactor(node->l_son) <= 0) {
      node = RightRotate(node);
    } else {
      node->l_son = LeftRotate(node->l_son);
      node = RightRotate(node);
    }
  }
  return node;
}

Node* Add(AVL& avl_tree, Node* new_node) {
  int64_t is_same = 0;
  Node* a = nullptr;
  Node* b = avl_tree.rt;
  while (b != nullptr) {
    if (new_node->value != b->value) {
      a = b;
      if (b->value > new_node->value) {
        b = b->l_son;
      } else {
        b = b->r_son;
      }
    } else {
      is_same = 1;
      break;
    }
  }
  if (is_same == 1) {
    delete new_node;
    return avl_tree.rt;
  }
  if (a == nullptr) {
    avl_tree.rt = new_node;
    return new_node;
  }
  new_node->prnt = a;
  if (a->value > new_node->value) {
    a->l_son = new_node;
  } else {
    a->r_son = new_node;
  }
  a->height = Max(Height(a->l_son) + 1, Height(a->r_son) + 1);
  while (a->prnt != nullptr) {
    a = a->prnt;
    a = Balance(a);
  }
  return a;
}

int64_t Next(AVL& avl_tree, int64_t value) {
  Node* b = avl_tree.rt;
  int64_t tmp = 0;
  while (!(b == nullptr || b->value == value)) {
    if (b->value >= value) {
      tmp = b->value;
    }
    if (b->value <= value) {
      b = b->r_son;
    } else {
      b = b->l_son;
    }
  }
  if (b != nullptr) {
    return value;
  }
  if (tmp >= value) {
    return tmp;
  }
  return -1;
}

void Clear(Node* node) {
  if (node != nullptr) {
    Clear(node->r_son);
    Clear(node->l_son);
    delete node;
  }
}