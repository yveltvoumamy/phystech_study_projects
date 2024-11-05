#include <iostream>
#include <vector>

class RandGen {
public:
  RandGen(unsigned a, unsigned b) : a_(a), b_(b) {
  }
  unsigned operator()() {
    cur_ = cur_ * a_ + b_;
    return cur_ >> 8;
  }
  unsigned a_ = 0;
  unsigned b_ = 0;
  unsigned cur_ = 0;
};

int main() {
  int m = 0;
  int q = 0;
  std::cin >> m >> q;
  int a = 0;
  int b = 0;
  std::cin >> a >> b;
  RandGen next_rand(a, b);

  const int k_size = (1 << 24);
  std::vector<int> delta(k_size + 1);

  while (m-- > 0) {
    unsigned add = next_rand();
    unsigned l = next_rand();
    unsigned r = next_rand();
    if (l > r) {
      std::swap(l, r);
    }
    delta[l] += static_cast<int>(add);
    delta[r + 1] -= static_cast<int>(add);
  }

  std::vector<unsigned> arr(k_size + 1);
  arr[0] = delta[0];
  for (int i = 1; i < k_size; ++i) {
    arr[i] = arr[i - 1] + delta[i];
  }

  std::vector<unsigned> prefsum(k_size + 1);
  for (int i = 0; i < k_size; ++i) {
    prefsum[i + 1] = prefsum[i] + arr[i];
  }

  unsigned ans = 0;
  while (q-- > 0) {
    unsigned l = next_rand();
    unsigned r = next_rand();
    if (l > r) {
      std::swap(l, r);
    }
    ans += prefsum[r + 1] - prefsum[l];
  }
  std::cout << ans;

  return 0;
}
