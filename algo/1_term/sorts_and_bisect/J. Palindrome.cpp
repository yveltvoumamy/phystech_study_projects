#include <iostream>
#include <cstdint>

bool CheckBoard(const int64_t w, const int64_t h, const int64_t n, const int64_t answer) {
  int64_t weight = answer / w;
  int64_t height = answer / h;
  return (weight * height >= n);
}

int64_t BinarySearch(int64_t begin, int64_t end, const int64_t w, const int64_t h, const int64_t n) {
  int64_t mid = 0;
  while (end - begin > 0) {
    mid = (end + begin) / 2;
    if (CheckBoard(w, h, n, mid)) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return end;
}

int64_t FindMax(const int64_t w, const int64_t h, const int64_t n) {
  int64_t maximum = w > h ? w : h;
  return maximum * n;
}

int main() {
  int64_t w;
  int64_t h;
  int64_t n;
  int64_t answer = 0;
  std::cin >> w;
  std::cin >> h;
  std::cin >> n;
  int64_t maximum = FindMax(w, h, n);
  answer = BinarySearch(0, maximum + 1, w, h, n);
  std::cout << answer;
  return 0;
}