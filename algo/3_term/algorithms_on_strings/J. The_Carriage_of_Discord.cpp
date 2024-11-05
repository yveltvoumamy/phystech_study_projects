#include <iostream>
#include <string>

void ZFunc(std::string s, size_t* z);

int main() {
  std::string first;
  std::string second;
  std::string new_str;
  bool flag = false;
  size_t n = 0;
  std::cin >> first >> second;
  new_str = first + '#' + second;
  auto zf = new size_t[new_str.size()]{};
  ZFunc(new_str, zf);
  size_t len = new_str.size();
  size_t first_len = first.size();
  first_len++;
  size_t second_len = len - first_len;
  auto pref_i_pos = new size_t[second_len];
  size_t i_max = len - second_len;
  if (zf[i_max] == 0) {
    flag = true;
  } else {
    size_t i = i_max;
    while (i < len) {
      if ((zf[i] == 0) && (i_max) <= i) {
        flag = true;
        break;
      }
      if (i + zf[i] >= i_max) {
        i_max = i + zf[i];
        pref_i_pos[n] = i;
        n++;
      }
      ++i;
    }
  }
  if (flag) {
    std::cout << "Yes";
    delete[] pref_i_pos;
    delete[] zf;
    return 0;
  }
  std::cout << "No" << '\n';
  size_t new_pos = pref_i_pos[1] - first_len;
  size_t i = 1;
  size_t j = 0;
  size_t last_pos = 0;
  while (i < n) {
    j = last_pos;
    while (j < new_pos) {
      std::cout << second[j];
      ++j;
    }
    std::cout << ' ';
    last_pos = new_pos;
    new_pos = pref_i_pos[(i + 1) % second_len] - first_len;
    ++i;
  }
  j = last_pos;
  while (j < second_len) {
    std::cout << second[j];
    j++;
  }
  delete[] pref_i_pos;
  delete[] zf;
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
