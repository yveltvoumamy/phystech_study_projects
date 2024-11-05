#include <iostream>
#include <map>
#include <string>
#include <vector>

class Node {
public:
  std::map<char, size_t> dict;
  bool term = false;
  Node() = default;
};

class Tree {
public:
  std::vector<Node> tree_;
  void Insert(std::string s) {
    size_t idx = 0;
    size_t i = 0;
    while (i < s.size()) {
      if (!(tree_[idx].dict.count(s[i]) == 0)) {
        idx = tree_[idx].dict[s[i]];
        i++;
      } else {
        Node node = Node();
        tree_.emplace_back(node);
        tree_[idx].dict[s[i]] = (tree_.size()) - 1;
        idx = tree_[idx].dict[s[i]];
        i++;
      }
    }
    tree_[idx].term = true;
  }
  bool Request(std::string s) {
    size_t idx = 0;
    size_t i = 0;
    while (i < s.size()) {
      if (tree_[idx].dict.count(s[i])) {
        idx = tree_[idx].dict[s[i]];
        i++;
      } else {
        return false;
      }
    }
    return tree_[idx].term;
  }
  Tree() {
    Node root;
    tree_.emplace_back(root);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  char symbol = 0;
  std::cin >> symbol;
  Tree tree;
  for (; symbol != '#';) {
    std::cin >> str;
    switch (symbol) {
      case '+':
        tree.Insert(str);
        break;
      case '?':
        std::string result = tree.Request(str) ? "YES\n" : "NO\n";
        std::cout << result;
        break;
    }
    std::cin >> symbol;
  }
}
