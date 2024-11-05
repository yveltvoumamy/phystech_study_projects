#include <iostream>
#include <string>

void ZFunc(std::string s, size_t* z);

int main() {
  int size = 0;
  std::cin >> size;
  std::string second;
  std::string first;
  std::cin >> first;
  std::cin >> second;
  bool flag = false;
  size_t ans = 0;
  size_t first_size = first.size();
  char charr = '0';
  size_t new_size = 2 + 3 * first_size;
  size_t j = 0;
  while (j < 2) {
    std::string new_first(first + '#' + second + charr + second);
    auto z_function = new size_t[new_first.size()]{};
    ZFunc(new_first, z_function);
    size_t i = first_size + 1;
    while (new_size > i) {
      if (first_size == z_function[i]) {
        if ('1' == charr) {
          ++ans;
        } else if ('0' == charr) {
          ++ans;
          flag = true;
        }
        break;
      }
      i++;
    }
    charr++;
    delete[] z_function;
    j++;
  }
  if (ans == 2) {
    std::cout << "Random";
  } else if (flag) {
    std::cout << "No";
  } else {
    std::cout << "Yes";
  }
  return 0;
}

void ZFunc(std::string s, size_t* z) {
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
}
