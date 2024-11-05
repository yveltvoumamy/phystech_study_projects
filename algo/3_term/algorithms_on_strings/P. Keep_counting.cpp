#include <iostream>
#include <string>
#include <map>
#include <vector>

struct State {
  int64_t size;
  int64_t link;
  int64_t prefix;
  int64_t pos_end;
  std::map<char, int64_t> mp;
};

class SuffixAutomate {
  public:
  void AddChar(char c) {
    ++len;
    int64_t curr = len;
    arr[curr].pos_end = arr[curr].size - 1;  //
    arr[curr].size = arr[last].size + 1;
    int64_t p = last;
    while (p != -1 && arr[p].mp.end() == arr[p].mp.find(c)) {
      arr[p].mp[c] = curr;
      p = arr[p].link;
    }
    if (p != -1) {
      int64_t q = arr[p].mp[c];
      if (arr[q].size != arr[p].size + 1) {
        ++len;
        arr[len].link = arr[q].link;
        arr[len].mp = arr[q].mp;
        arr[len].size = arr[p].size + 1;
        arr[len].pos_end = arr[q].pos_end;  //
        while (p != -1 && arr[p].mp[c] == q) {
          arr[p].mp[c] = len;
          p = arr[p].link;
        }
        arr[curr].link = len;
        arr[q].link = len;
      } else {
        arr[curr].link = q;
      }
    } else {
      arr[curr].link = 0;
    }
    arr[curr].prefix = arr[curr].size + arr[last].prefix - arr[arr[curr].link].size;
    std::cout << arr[curr].prefix << '\n';
    last = curr;
  }
  int64_t last;
  std::vector<State> arr;
  int64_t len;
  SuffixAutomate() : arr(0) {
    last = 0;
    len = 0;
    arr[0].link = -1;
    arr[0].size = 0;
  }
  explicit SuffixAutomate(std::string s) : arr(2 * s.size()) {
    last = 0;
    len = 0;
    arr[0].link = -1;
    arr[0].size = 0;
    arr[0].pos_end = 0;
    int64_t i = 0;
    while (static_cast<size_t>(i) < s.size()) {
      AddChar(s[i]);
      ++i;
    }
  }
  explicit SuffixAutomate(int64_t q) : arr(2 * q) {
    last = 0;
    len = 0;
    arr[0].link = -1;
    arr[0].size = 0;
    arr[0].pos_end = 0;
  }
  bool Find(const int64_t len) {
    return arr[arr[last].link].size < len;
  }
};
int main() {
  std::string str;
  std::cin >> str;
  SuffixAutomate suff_aut(str);
}
