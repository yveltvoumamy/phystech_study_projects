#include <iostream>
#include <string>

void ZFunc(std::string s);

int main() {
  std::string s;
  std::cin >> s;
  ZFunc(s);
  return 0;
}

void ZFunc(std::string s) {
  auto z = new size_t[s.size()]{};
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 1; i < s.size(); i++) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  z[0] = s.size();
  for (size_t i = 0; i < s.size(); i++) {
    std::cout << z[i] << ' ';
  }
  delete[] z;
}
