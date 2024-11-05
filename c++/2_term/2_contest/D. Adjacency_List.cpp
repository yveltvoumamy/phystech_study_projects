#include <iostream>
#include <vector>

int main() {
  int32_t n;
  int32_t k;
  int32_t u;
  int32_t v;
  int32_t i = 0;
  std::cin >> n;
  n++;
  int32_t command;
  std::vector<std::vector<int32_t>> arr(n--);
  std::cin >> k;
  while (i < k) {
    std::cin >> command;
    if (!(command % 2)) {
      std::cin >> u;
      int32_t size = arr[u].size();
      int32_t j = 0;
      while (j < size) {
        std::cout << arr[u][j] << ' ';
        ++j;
      }
      std::cout << '\n';
    } else {
      std::cin >> u >> v;
      arr[v].push_back(u);
      arr[u].push_back(v);
    }
    i++;
  }
}