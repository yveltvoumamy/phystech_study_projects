#include <iostream>
#include <vector>

const int64_t kInf = 1e17;

class SegmentTree {
public:
  explicit SegmentTree(std::vector<int64_t>& array);

  int64_t Get(int left, int right);

  void Update(int left, int right, int value);

private:
  void Build(int vert, int left, int right, std::vector<int64_t>& a);

  void Push(int vert, int left, int right);

  void Update(int vert, int left, int right, int q_left, int q_right, int val);

  int64_t Get(int vert, int left, int right, int q_left, int q_right);

  std::vector<int64_t> tree_, add_;
  int size_;
};

SegmentTree::SegmentTree(std::vector<int64_t>& array) {
  size_ = static_cast<int>(array.size());
  int ps = 1;
  while (ps < size_) {
    ps *= 2;
  }
  tree_.assign(2 * ps, -kInf);
  add_.assign(2 * ps, 0);
  Build(0, 0, size_, array);
}

void SegmentTree::Build(int vert, int left, int right, std::vector<int64_t>& a) {
  if (right - left == 1) {
    tree_[vert] = a[left];
    return;
  }
  int middle = left + (right - left) / 2;
  Build(2 * vert + 1, left, middle, a);
  Build(2 * vert + 2, middle, right, a);
  tree_[vert] = std::max(tree_[2 * vert + 1], tree_[2 * vert + 2]);
}

void SegmentTree::Push(int vert, int left, int right) {
  if (add_[vert] == 0) {
    return;
  }
  int64_t val = add_[vert];
  add_[vert] = 0;
  tree_[vert] += val;
  if (right - left > 1) {
    add_[2 * vert + 1] += val;
    add_[2 * vert + 2] += val;
  }
}

void SegmentTree::Update(int vert, int left, int right, int q_left, int q_right, int val) {
  Push(vert, left, right);
  if (left >= q_right || right <= q_left) {
    return;
  }
  if (left >= q_left && right <= q_right) {
    add_[vert] += val;
    Push(vert, left, right);
    return;
  }
  int middle = left + (right - left) / 2;
  Update(2 * vert + 1, left, middle, q_left, q_right, val);
  Update(2 * vert + 2, middle, right, q_left, q_right, val);
  tree_[vert] = std::max(tree_[2 * vert + 1], tree_[2 * vert + 2]);
}

int64_t SegmentTree::Get(int vert, int left, int right, int q_left, int q_right) {
  Push(vert, left, right);
  if (left >= q_right || right <= q_left) {
    return -kInf;
  }
  if (left >= q_left && right <= q_right) {
    return tree_[vert];
  }
  int middle = left + (right - left) / 2;
  return std::max(Get(2 * vert + 1, left, middle, q_left, q_right), Get(2 * vert + 2, middle, right, q_left, q_right));
}

int64_t SegmentTree::Get(int left, int right) {
  return Get(0, 0, size_, left - 1, right);
}

void SegmentTree::Update(int left, int right, int value) {
  Update(0, 0, size_, left - 1, right, value);
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size = 0;
  std::cin >> size;
  std::vector<int64_t> number(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> number[i];
  }
  SegmentTree tree(number);
  int query = 0;
  std::cin >> query;
  while (query-- > 0) {
    char type = 'a';
    std::cin >> type;
    if (type == 'm') {
      int left = 0;
      int right = 0;
      std::cin >> left >> right;
      std::cout << tree.Get(left, right) << ' ';
    } else {
      int left = 0;
      int right = 0;
      int val = 0;
      std::cin >> left >> right >> val;
      tree.Update(left, right, val);
    }
  }
}