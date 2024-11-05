#include <iostream>
#include <vector>

int Gcd(int first, int second) {
  if (second == 0) {
    return first;
  }
  return Gcd(second, first % second);
}

class SegmentTree {
public:
  explicit SegmentTree(std::vector<int>& array);

  int Get(int left, int right);

private:
  void Build(int vert, int left, int right, std::vector<int>& array);

  int Get(int vert, int left, int right, int q_left, int q_right);

  std::vector<int> tree_;
  int size_;
};

SegmentTree::SegmentTree(std::vector<int>& array) {
  int arr_size = 1;
  while (arr_size < static_cast<int>(array.size())) {
    arr_size *= 2;
  }
  size_ = static_cast<int>(array.size());
  tree_.assign(arr_size * 2, 0);
  Build(0, 0, size_, array);
}

void SegmentTree::Build(int vert, int left, int right, std::vector<int>& array) {
  if (right - left == 1) {
    tree_[vert] = array[left];
    return;
  }
  int middle = left + (right - left) / 2;
  Build(2 * vert + 1, left, middle, array);
  Build(2 * vert + 2, middle, right, array);
  tree_[vert] = Gcd(tree_[2 * vert + 1], tree_[2 * vert + 2]);
}

int SegmentTree::Get(int vert, int left, int right, int q_left, int q_right) {
  if (left >= q_right || right <= q_left) {
    return 0;
  }
  if (left >= q_left && right <= q_right) {
    return tree_[vert];
  }
  int middle = left + (right - left) / 2;
  return Gcd(Get(2 * vert + 1, left, middle, q_left, q_right), Get(2 * vert + 2, middle, right, q_left, q_right));
}

int SegmentTree::Get(int left, int right) {
  return Get(0, 0, size_, left - 1, right);
}

int main() {
  int size = 0;
  std::cin >> size;
  std::vector<int> array(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  SegmentTree tree(array);
  int query = 0;
  std::cin >> query;
  while (query-- > 0) {
    int left = 0;
    int right = 0;
    std::cin >> left >> right;
    std::cout << tree.Get(left, right) << '\n';
  }
}