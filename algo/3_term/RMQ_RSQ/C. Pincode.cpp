#include <iostream>
#include <vector>

const int kInf = 1e9 + 1;

class SegmentTree {
public:
  explicit SegmentTree(std::vector<int>& array);

  int Get(int left, int right);

private:
  int Get(int vert, int left, int right, int q_left, int q_right);

  void Build(int vert, int left, int right, std::vector<int>& array);

  std::vector<int> tree_;
  int size_;
};

SegmentTree::SegmentTree(std::vector<int>& array) {
  int ps = 1;
  size_ = static_cast<int>(array.size());
  while (ps < size_) {
    ps *= 2;
  }
  tree_.assign(2 * ps, kInf);
  Build(0, 0, size_, array);
}

int SegmentTree::Get(int left, int right) {
  return Get(0, 0, size_, left - 1, right);
}

int SegmentTree::Get(int vert, int left, int right, int q_left, int q_right) {
  if (left >= q_right || right <= q_left) {
    return kInf;
  }
  if (left >= q_left && right <= q_right) {
    return tree_[vert];
  }
  int middle = left + (right - left) / 2;
  return std::min(Get(2 * vert + 1, left, middle, q_left, q_right), Get(2 * vert + 2, middle, right, q_left, q_right));
}

void SegmentTree::Build(int vert, int left, int right, std::vector<int>& array) {
  if (right - left == 1) {
    tree_[vert] = array[left];
    return;
  }
  int middle = left + (right - left) / 2;
  Build(2 * vert + 1, left, middle, array);
  Build(2 * vert + 2, middle, right, array);
  tree_[vert] = std::min(tree_[2 * vert + 1], tree_[2 * vert + 2]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size = 0;
  int query = 0;
  std::cin >> size;
  std::cin >> query;
  std::vector<int> numbers(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> numbers[i];
  }
  SegmentTree tree(numbers);
  while (query-- > 0) {
    int left = 0;
    int right = 0;
    std::cin >> left >> right;
    std::cout << tree.Get(left, right) << '\n';
  }
}