#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int32_t n;
  std::cin >> n;
  std::vector<int32_t> arr(n);
  int32_t i = 0;
  while (i < n) {
    std::cin >> arr[i];
    i++;
  }
  int32_t value;
  std::cin >> value;
  std::cout << count(arr.begin(), arr.end(), value);
}