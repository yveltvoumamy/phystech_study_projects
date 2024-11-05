#include <iostream>
#include <vector>

int main() {
  int size = 0;
  std::cin >> size;
  std::vector<int64_t> numbers(size + 1, 0);
  for (int i = 1; i <= size; ++i) {
    std::cin >> numbers[i];
  }
  for (int i = 1; i <= size; ++i) {
    numbers[i] += numbers[i - 1];
  }
  int query = 0;
  std::cin >> query;
  while (query-- > 0) {
    int left = 0;
    int right = 0;
    std::cin >> left >> right;
    std::cout << numbers[right] - numbers[left - 1] << ' ';
  }
}