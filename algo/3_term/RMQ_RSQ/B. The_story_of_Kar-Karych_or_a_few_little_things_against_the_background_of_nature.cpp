#include <iostream>
#include <vector>

int main() {
  int size = 0;
  std::cin >> size;
  std::vector<int> numbers(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> numbers[i];
  }
  int ans = numbers[0];
  int ans_left = 0;
  int ans_right = 0;
  int sum = 0;
  int min_sum = 0;
  int min_pos = -1;
  for (int idx = 0; idx < size; ++idx) {
    sum += numbers[idx];
    int cur = sum - min_sum;
    if (cur > ans) {
      ans = cur;
      ans_left = min_pos + 1;
      ans_right = idx;
    }
    if (sum < min_sum) {
      min_sum = sum;
      min_pos = idx;
    }
  }
  std::cout << ans_left + 1 << ' ' << ans_right + 1 << ' ' << ans;
}