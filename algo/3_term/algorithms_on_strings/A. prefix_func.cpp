#include <iostream>
#include <string>

void PrefixFunc(std::string s);

int main() {
  std::string s;
  std::cin >> s;
  PrefixFunc(s);
  return 0;
}

void PrefixFunc(std::string s) {
  auto p = new int[s.size()]{};
  for (size_t i = 1; i < s.size(); i++) {
    int k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }
  for (size_t i = 0; i < s.size(); i++) {
    std::cout << p[i] << ' ';
  }
  delete[] p;
}
