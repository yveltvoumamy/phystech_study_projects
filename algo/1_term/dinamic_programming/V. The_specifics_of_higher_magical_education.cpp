#include <iostream>

void Clean(int64_t* arr, int64_t** dp, int64_t n1);
void Input(int64_t* arr, int64_t n);
void CreateDiagonalMatrix(int64_t** dp, int64_t n1);
void GetAnswer(int64_t** dp, int64_t* arr, int64_t n1);

int main() {
  int64_t n;
  std::cin >> n;
  int64_t n1 = n - 1;
  auto arr = new int64_t[n];
  auto dp = new int64_t*[n1];
  Input(arr, n);
  CreateDiagonalMatrix(dp, n1);
  GetAnswer(dp, arr, n1);
  std::cout << dp[0][n1 - 1] << '\n';
  Clean(arr, dp, n1);
}

void GetAnswer(int64_t** dp, int64_t* arr, int64_t n1) {
  int64_t l = 1;
  while (l < n1) {
    int64_t i = 0;
    while (i < n1 - l) {
      int64_t j = i + l;
      dp[i][j] = 348157075;
      int64_t k = i;
      while (k < j) {
        dp[i][j] = std::min(dp[i][j], dp[k + 1][j] + arr[k + 1] * arr[i] * arr[j + 1] + dp[i][k]);
        k++;
      }
      i++;
    }
    l++;
  }
}

void CreateDiagonalMatrix(int64_t** dp, int64_t n1) {
  for (int i = 0; i < n1; ++i) {
    dp[i] = new int64_t[n1];
    dp[i][i] = 0;
  }
}

void Input(int64_t* arr, int64_t n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
}

void Clean(int64_t* arr, int64_t** dp, int64_t n1) {
  delete[] arr;
  for (int i = 0; i < n1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
}