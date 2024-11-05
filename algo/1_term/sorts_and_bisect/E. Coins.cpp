#include <iostream>

void Change(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
            bool& more, int& sum);
void FirstSycle(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
                bool& more, int& sum);
void SecondSycle(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
                 bool& more, int& sum);
void Copy(int64_t* a, int64_t* b, int len);
void Copy(int64_t* a, int64_t* b, int len);
void Plus(int& sum, int64_t** a, int st, int i, int& used, int64_t* sch);
void Minus(int& sum, int64_t** a, int st, int i, int& used, int64_t* sch);
void Clean(int64_t* arr2, int64_t* minor, int64_t* sch, int64_t** array, int n);
void CreateArrays(int64_t* arr2, int64_t** array, int64_t* sch, int n);
void Input(int64_t* arr2, int n);
void Output(bool more, int min, int n, int64_t* minarr, int64_t* arr2);

int main() {
  bool less = false;
  bool more = false;
  int n;
  int used = 0;
  int min = 32;
  int sum = 0;
  int64_t isk;
  std::cin >> isk >> n;
  auto arr2 = new int64_t[n];
  auto sch = new int64_t[n];
  auto minarr = new int64_t[n];
  auto array = new int64_t*[n];
  CreateArrays(arr2, array, sch, n);
  Copy(sch, minarr, n);
  Change(array, used, n, 0, isk, sch, minarr, min, less, more, sum);
  Output(more, min, n, minarr, arr2);
  Clean(arr2, minarr, sch, array, n);
}

void Output(bool more, int min, int n, int64_t* minarr, int64_t* arr2) {
  if (!(more)) {
    std::cout << "-1";
  } else if (more && (min == 32)) {
    std::cout << '0';
  } else {
    std::cout << min << ' ';
    for (int i = 0; i < n; i++) {
      int y = minarr[i];
      while (y > 0) {
        std::cout << arr2[i] << '\n';
        y--;
      }
    }
  }
}

void CreateArrays(int64_t* arr2, int64_t** array, int64_t* sch, int n) {
  for (int i = 0; i < n; i++) {
    array[i] = new int64_t[3];
  }
  Input(arr2, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      array[i][j] = arr2[i] * j;
    }
  }
  for (int i = 0; i < n; i++) {
    sch[i] = 0;
  }
}

void Input(int64_t* arr2, int n) {
  for (int i = 0; i < n; i++) {
    std::cin >> arr2[i];
  }
}

void Copy(int64_t* a, int64_t* b, int len) {
  for (int i = 0; i < len; i++) {
    b[i] = a[i];
  }
}

void Clean(int64_t* arr2, int64_t* minor, int64_t* sch, int64_t** array, int n) {
  delete[] arr2;
  delete[] minor;
  delete[] sch;
  for (int i = 0; i < n; i++) {
    delete[] array[i];
  }
  delete[] array;
}

void Change(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
            bool& more, int& sum) {
  if (st == n - 1) {
    FirstSycle(a, used, n, st, nado, sch, minar, min, less, more, sum);
    return;
  }
  SecondSycle(a, used, n, st, nado, sch, minar, min, less, more, sum);
}

void FirstSycle(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
                bool& more, int& sum) {
  for (int i = 0; i < 3; i++) {
    Plus(sum, a, st, i, used, sch);
    if (sum == nado) {
      if (used < min) {
        min = used;
        Copy(sch, minar, n);
      }
      more = true;
    } else if (sum < nado) {
      less = true;
    } else {
      more = true;
    }
    Minus(sum, a, st, i, used, sch);
  }
}

void SecondSycle(int64_t** a, int used, int n, int st, int64_t nado, int64_t* sch, int64_t* minar, int& min, bool& less,
                 bool& more, int& sum) {
  for (int32_t i = 0; i < 3; i++) {
    Plus(sum, a, st, i, used, sch);
    if (sum == nado) {
      if (used < min) {
        min = used;
        Copy(sch, minar, n);
      }
    } else if (sum < nado) {
      Change(a, used, n, st + 1, nado, sch, minar, min, less, more, sum);
    } else {
      more = true;
    }
    Minus(sum, a, st, i, used, sch);
  }
}

void Plus(int& sum, int64_t** a, int st, int i, int& used, int64_t* sch) {
  sum += a[st][i];
  used += i;
  sch[st] += i;
}

void Minus(int& sum, int64_t** a, int st, int i, int& used, int64_t* sch) {
  sum -= a[st][i];
  used -= i;
  sch[st] -= i;
}