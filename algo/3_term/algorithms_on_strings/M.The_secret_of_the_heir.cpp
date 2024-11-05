#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

struct Borders {
  int64_t left;
  int64_t right;
  size_t idx;
  Borders(int64_t new_left, int64_t new_right, size_t new_idx) {
    left = new_left;
    right = new_right;
    idx = new_idx;
  }
};

struct Node {
  std::map<char, int32_t> next;
  std::vector<Borders> borders;
  int32_t link;
  int32_t term_link;
  size_t idx;
  size_t len;
  bool is_term = false;
  Node() = default;
};

struct SuffQueue {
  size_t curr_node_idx;
  size_t parent;
  char symbol;
  SuffQueue(char symbol_new, size_t parent_new, size_t curr_node_idx_new) {
    symbol = symbol_new;
    parent = parent_new;
    curr_node_idx = curr_node_idx_new;
  }
  SuffQueue() = default;
};

class Tree {
public:
  std::vector<Node> st;
  std::vector<size_t> result_index;

  void Insert(std::string s, size_t order, int32_t left, int32_t right) {
    size_t idx_curr_node = 0;
    for (auto c : s) {
      size_t idx_next = st[idx_curr_node].next[c];
      if (idx_next) {
        idx_curr_node = idx_next;
      } else {
        Node node = Node();
        st.emplace_back(node);
        idx_next = static_cast<int32_t>(st.size() - 1);
        st[idx_curr_node].next[c] = static_cast<int32_t>(idx_next);
        idx_curr_node = idx_next;
      }
    }
    st[idx_curr_node].idx = order;
    st[idx_curr_node].is_term = true;
    st[idx_curr_node].len = s.size();
    Borders new_border(left, right, order);
    st[idx_curr_node].borders.push_back(new_border);
  }

  void BuildSuffixReferences() {
    st[0].link = -1;
    std::queue<SuffQueue> q;
    for (auto p : st[0].next) {
      SuffQueue suff_q = SuffQueue(p.first, 0, p.second);
      q.emplace(suff_q);
    }
    SuffQueue tmp;
    for (; !q.empty();) {
      tmp = q.front();
      int32_t suff_link = st[tmp.parent].link;
      size_t ind_suff = tmp.parent;
      q.pop();
      for (; (-1 != suff_link) && (st[suff_link].next.end() == st[suff_link].next.find(tmp.symbol));) {
        suff_link = st[ind_suff].link;
        ind_suff = suff_link;
      }
      if (suff_link != -1) {
        st[tmp.curr_node_idx].link = st[suff_link].next[tmp.symbol];
      } else {
        st[tmp.curr_node_idx].link = 0;
      }
      for (auto p : st[tmp.curr_node_idx].next) {
        SuffQueue suff_q = SuffQueue(p.first, tmp.curr_node_idx, p.second);
        q.emplace(suff_q);
      }
    }
  }
  void BuildExitSuffixReferences() {
    st[0].term_link = -1;
    std::queue<size_t> q;
    for (auto p : st[0].next) {
      q.push(p.second);
    }
    size_t tmp = 0;
    for (; !q.empty();) {
      tmp = q.front();
      int32_t suff_link = st[tmp].link;
      q.pop();
      if (suff_link != 0) {
        if (!st[suff_link].is_term) {
          st[tmp].term_link = st[suff_link].term_link;
        } else {
          st[tmp].term_link = suff_link;
        }
      }
      for (auto p : st[tmp].next) {
        q.push(p.second);
      }
    }
  }
  explicit Tree(size_t size) {
    Node node = Node();
    st.emplace_back(node);
    std::string str;
    result_index.resize(size);
    int32_t left = 0;
    int32_t right = 0;
    size_t i = 0;
    while (i < size) {
      std::cin >> left >> right;
      std::cin >> str;
      Insert(str, i, left, right);
      ++i;
    }
    BuildSuffixReferences();
    BuildExitSuffixReferences();
  }
  int32_t NextState(int32_t idx, char c) {
    for (; (-1 != idx) && (st[idx].next.end() == st[idx].next.find(c));) {
      idx = static_cast<int32_t>(st[idx].link);
    }
    if (idx == -1) {
      return 0;
    }
    return st[idx].next[c];
  }
  void PrintEntries(size_t idx, int32_t node_idx) {
    if (!st[node_idx].is_term) {
      node_idx = st[node_idx].term_link;
    }
    for (; (node_idx != 0) && (node_idx != -1);) {
      int32_t i = 0;
      while (i < static_cast<int32_t>(st[node_idx].borders.size())) {
        if ((static_cast<int64_t>(idx + 1) <= st[node_idx].borders[i].right) &&
            (static_cast<int64_t>(idx - st[node_idx].len + 2) >= st[node_idx].borders[i].left)) {
          result_index[st[node_idx].borders[i].idx] = 1;
        }
        i++;
      }
      node_idx = st[node_idx].term_link;
    }
  }
};

void AhoCorasik(std::string& s, size_t size_p) {
  Tree tree(size_p);
  int32_t node = 0;
  size_t i = 0;
  while (i < s.size()) {
    node = tree.NextState(node, s[i]);
    tree.PrintEntries(i, node);
    i++;
  }
  i = 0;
  size_t quantity_patterns = tree.result_index.size();
  for (size_t i = 0; i < quantity_patterns; ++i) {
    if (tree.result_index[i]) {
      std::cout << '+';
    } else {
      std::cout << '-';
    }
  }
}

int main() {
  std::string str;
  std::cin >> str;
  size_t size_dict = 0;
  std::cin >> size_dict;
  AhoCorasik(str, size_dict);
  return 0;
}