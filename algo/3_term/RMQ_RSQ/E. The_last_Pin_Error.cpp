#include <iostream>
#include <vector>

class SegmentTree {
public:
  explicit SegmentTree(std::vector<int64_t>& array);

  int64_t Get(int left, int right);

  void Update(int pos, int value);

private:
  int64_t Get(int vert, int left, int right, int q_left, int q_right);

  void Build(int vert, int left, int right, std::vector<int64_t>& array);

  void Update(int vert, int left, int right, int pos, int value);

  std::vector<int64_t> tree_;
  int size_;
};

SegmentTree::SegmentTree(std::vector<int64_t>& array) {
  int ps = 1;
  size_ = static_cast<int>(array.size());
  while (ps < size_) {
    ps *= 2;
  }
  tree_.assign(2 * ps, 0);
  Build(0, 0, size_, array);
}

int64_t SegmentTree::Get(int left, int right) {
  return Get(0, 0, size_, left - 1, right);
}

void SegmentTree::Update(int pos, int value) {
  Update(0, 0, size_, pos, value);
}

int64_t SegmentTree::Get(int vert, int left, int right, int q_left, int q_right) {
  if (left >= q_right || right <= q_left) {
    return 0;
  }
  if (left >= q_left && right <= q_right) {
    return tree_[vert];
  }
  int middle = left + (right - left) / 2;
  return Get(2 * vert + 1, left, middle, q_left, q_right) + Get(2 * vert + 2, middle, right, q_left, q_right);
}

void SegmentTree::Build(int vert, int left, int right, std::vector<int64_t>& array) {
  if (right - left == 1) {
    tree_[vert] = array[left];
    return;
  }
  int middle = left + (right - left) / 2;
  Build(2 * vert + 1, left, middle, array);
  Build(2 * vert + 2, middle, right, array);
  tree_[vert] = tree_[2 * vert + 1] + tree_[2 * vert + 2];
}

void SegmentTree::Update(int vert, int left, int right, int pos, int value) {
  if (left > pos || right <= pos) {
    return;
  }
  if (left == pos && right - left == 1) {
    tree_[vert] = value;
    return;
  }
  int middle = left + (right - left) / 2;
  Update(2 * vert + 1, left, middle, pos, value);
  Update(2 * vert + 2, middle, right, pos, value);
  tree_[vert] = tree_[2 * vert + 1] + tree_[2 * vert + 2];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size = 0;
  int query = 0;
  std::cin >> size;
  std::vector<int64_t> numbers(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> numbers[i];
  }
  std::cin >> query;
  SegmentTree tree(numbers);
  while (query-- > 0) {
    char type = 'a';
    int left = 0;
    int right = 0;
    std::cin >> type >> left >> right;
    if (type == 's') {
      std::cout << tree.Get(left, right) << ' ';
    } else {
      tree.Update(left - 1, right);
    }
  }
}