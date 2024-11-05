#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int n, i;
  std::cin >> n;
  std::vector<int32_t> array(n);
  i = 0;
  while (i < n) {
    std::cin >> array[i];
    ++i;
  }
  int32_t m;
  std::cin >> m;
  int32_t command;
  i = 0;
  while (i < m) {
    std::cin >> command;
    std::cout << upper_bound(array.begin(), array.end(), command) - lower_bound(array.begin(), array.end(), command)
              << '\n';
    i++;
  }
}