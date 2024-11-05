#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

void ZTOPrefix(std::vector<int>& z, int zn, std::vector<int>& p) {
  for (int i = 1; i < zn; i++) {
    for (int j = z[i] - 1; j >= 0; j--) {
      if (i + j < zn && p[i + j] == 0) {
        p[i + j] = j + 1;
      } else {
        break;
      }
    }
  }
}

void PrefixToString(std::vector<int>& p, size_t n) {
  std::string s = "a";
  std::set<char> ban;
  size_t k = 0;
  for (size_t i = 1; i < n; i++) {
    if (p[i] > 0) {
      s += s[p[i] - 1];
    } else {
      ban.clear();
      k = p[i - 1];
      while (k > 0) {
        ban.insert(s[k]);
        k = p[k - 1];
      }
      for (char symbol = 'b'; symbol < 'z'; symbol++) {
        if (ban.find(symbol) == ban.end()) {
          s += symbol;
          break;
        }
      }
    }
  }
  std::cout << s;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size = 0;
  std::cin >> size;
  std::vector<int> zf(size, 0);
  std::vector<int> pf(size, 0);
  for (int i = 0; i < size; ++i) {
    std::cin >> zf[i];
  }
  ZTOPrefix(zf, size, pf);
  PrefixToString(pf, size);
  return 0;
}
