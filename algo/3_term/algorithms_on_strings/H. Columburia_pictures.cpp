#include <iostream>
#include <string>

size_t PrefixFunc(std::string s);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n = 0;
  std::cin >> n;
  std::string str1;
  std::string str2;
  std::cin >> str1;
  std::string new_str;
  size_t i = 2;
  while (i <= n) {
    std::cin >> str2;
    if (str2.size() >= str1.size()) {
      new_str = str2 + '#' + str1;
    } else {
      std::string tmp_first_part(static_cast<int64_t>(str1.size()) + str1.begin() - static_cast<int64_t>(str2.size()),
                                 str1.end());
      new_str = str2 + '#' + tmp_first_part;
    }
    size_t result = PrefixFunc(new_str);
    str1 += str2.substr(result);
    ++i;
  }
  std::cout << str1;
}

size_t PrefixFunc(std::string s) {
  size_t len = s.size();
  auto p = new int[len]{};
  for (size_t i = 1; i < len; i++) {
    int k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }
  size_t result = p[len - 1];
  delete[] p;
  return result;
}
