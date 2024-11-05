#include <iostream>

void FillArr(int64_t* arr, int64_t n);
void ReadST(int64_t* s, int64_t* t, int64_t q);
bool Possibly(int64_t s, int64_t t, int64_t* v, int64_t* l, int64_t e, int64_t n);
void BinarySearch(int64_t s, int64_t t, int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t m, int64_t n);
void SolutionForAllCars(int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t* s, int64_t* t, int64_t q, int64_t m,
                        int64_t n);
void Clean(int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t* s, int64_t* t);

int main() {
  int64_t m, n, q;
  std::cin >> n;
  auto v = new int64_t[n];
  auto l = new int64_t[n];
  FillArr(v, n);
  FillArr(l, n);
  std::cin >> m;
  auto a = new int64_t[m];
  auto f = new int64_t[m + 1];
  a[0] = 0;
  f[0] = 0;
  FillArr(a + 1, m - 1);
  FillArr(f + 1, m);
  std::cin >> q;
  auto s = new int64_t[q];
  auto t = new int64_t[q];
  ReadST(s, t, q);
  SolutionForAllCars(v, l, a, f, s, t, q, m, n);
  Clean(v, l, a, f, s, t);
}

void FillArr(int64_t* arr, int64_t n) {
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
}

void ReadST(int64_t* s, int64_t* t, int64_t q) {
  for (int i = 0; i < q; ++i) {
    std::cin >> s[i];
    std::cin >> t[i];
  }
}

bool Possibly(int64_t s, int64_t t, int64_t* v, int64_t* l, int64_t e, int64_t n) {
  double min_time = 0;
  for (int i = 0; i < n; ++i) {
    min_time += double(l[i]) / double(v[i] + e);
  }
  return (min_time <= t - s);
}

void BinarySearch(int64_t s, int64_t t, int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t m, int64_t n) {
  int left = -1;
  int right = m;
  while (right - left > 1) {
    int mid = left + (right - left) / 2;
    if (Possibly(s, t, v, l, a[mid], n)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  std::cout << f[right] << "\n";
}

void SolutionForAllCars(int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t* s, int64_t* t, int64_t q, int64_t m,
                        int64_t n) {
  for (int i = 0; i < q; ++i) {
    BinarySearch(s[i], t[i], v, l, a, f, m, n);
  }
}

void Clean(int64_t* v, int64_t* l, int64_t* a, int64_t* f, int64_t* s, int64_t* t) {
  delete[] v;
  delete[] l;
  delete[] a;
  delete[] f;
  delete[] s;
  delete[] t;
}
