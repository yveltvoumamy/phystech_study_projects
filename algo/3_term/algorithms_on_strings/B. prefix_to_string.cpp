#include <iostream>
#include <string>
#include <set>

void PrefixToString(size_t* p, size_t n);

int main() {
  std::string s;
  size_t n = 0;
  std::cin >> n;
  auto p = new size_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> p[i];
  }
  PrefixToString(p, n);
  delete[] p;
  return 0;
}

void PrefixToString(size_t* p, size_t n) {
  if (n == 0) {
    return;
  }
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
