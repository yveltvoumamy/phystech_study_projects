#include <iostream>
#include <cstring>
#include <cstdint>

int main() {
  int k;
  std::cin >> k;
  char string[1000001] = {};
  std::cin.getline(string, 0);
  std::cin.getline(string, 1000001);
  const int len = strlen(string);
  int64_t ans = 0;
  for (int i = 0; i < len - k; ++i) {
    int j = 0;
    int64_t counter = 0;
    while (string[i + j] == string[i + k + j]) {
      ++j;
      ++counter;
    }
    ans += (counter + 1) * counter / 2;
    i += counter;
  }
  std::cout << ans;
}