#include <iostream>
#include <string>

void PrefixFunc(std::string s, std::string sub);
void KMP(std::string s, std::string sub);

int main() {
  std::string s;
  std::string sub;
  std::cin >> s;
  std::cin >> sub;
  KMP(s, sub);
  return 0;
}

void KMP(std::string s, std::string sub) {
  std::string concatination = sub + '#' + s;
  PrefixFunc(concatination, sub);
}

void PrefixFunc(std::string s, std::string sub) {
  auto p = new size_t[s.size()]{};
  for (size_t i = 1; i < s.size(); i++) {
    size_t k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }
  for (size_t i = 0; i < s.size(); i++) {
    if (p[i] == sub.size()) {
      std::cout << i - (sub.size()) - sub.size() << ' ';
    }
  }
  delete[] p;
}
