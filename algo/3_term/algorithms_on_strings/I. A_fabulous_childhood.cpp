#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Palindrome(const int* num, int* pl, int len) {
  int l = 0;
  int r = 0;
  int i = 1;
  while (len > i) {
    if (i <= r) {
      pl[i] = std::max(std::min(pl[r + l - i + 1], r + 1 - i), 0);
    }
    for (; (0 <= i - 1 - pl[i]) && (len > pl[i] + i) && (num[i - 1 - pl[i]] == num[pl[i] + i]);) {
      ++pl[i];
    }
    if (r < pl[i] + i - 1) {
      r = pl[i] + i - 1;
      l = i - pl[i];
    }
    i++;
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  auto cubes = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> cubes[i];
  }
  auto pl = new int[n]{};
  Palindrome(cubes, pl, n);
  int i = n - 1;
  while (i >= 0) {
    if (i == pl[i]) {
      std::cout << n - pl[i] << ' ';
    }
    i--;
  }
  delete[] cubes;
  delete[] pl;
}
