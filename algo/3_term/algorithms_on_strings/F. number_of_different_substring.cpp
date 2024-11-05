#include <iostream>
#include <string>

size_t PrefixFunc(std::string s, size_t* p);

int main() {
  std::string str;
  std::cin >> str;
  std::string s;
  size_t words = 1;
  auto len_s = static_cast<int32_t>(str.size());
  for (int32_t i = 1; i < len_s; i++) {
    std::string tmp(std::make_reverse_iterator(str.begin() + i), str.rend());
    s = str[i] + tmp;
    auto p = new size_t[s.size()]{};
    size_t max_prefx = PrefixFunc(s, p);
    words += i + 1 - max_prefx;
    // std::cout << max_prefx << '\n';
    delete[] p;
  }
  std::cout << words;
  return 0;
}

size_t PrefixFunc(std::string s, size_t* p) {
  size_t max_prefix = 0;
  for (size_t i = 1; i < s.size(); i++) {
    size_t k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
    max_prefix = std::max(max_prefix, p[i]);
  }
  // std::cout << max_prefix << '\n';
  return max_prefix;
}
