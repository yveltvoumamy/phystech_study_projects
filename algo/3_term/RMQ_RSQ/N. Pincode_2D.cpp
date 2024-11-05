#include <iostream>

const int kMaxn = 510;

int ln[kMaxn];
int a[kMaxn][kMaxn];
int dp[10][10][kMaxn][kMaxn];

int main() {
  ln[1] = 0;
  for (int i = 2; i < kMaxn; ++i) {
    ln[i] = 1 + ln[i / 2];
  }
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> a[i][j];
      dp[0][0][i][j] = a[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int k = 1; k < 10; ++k) {
      for (int j = 0; j + (1 << k) <= m; ++j) {
        dp[0][k][i][j] = std::min(dp[0][k - 1][i][j], dp[0][k - 1][i][j + (1 << (k - 1))]);
      }
    }
  }
  for (int k = 1; k < 10; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int p = 0; p < 10; ++p) {
        for (int j = 0; j < m; ++j) {
          dp[k][p][i][j] = std::min(dp[k - 1][p][i][j], dp[k - 1][p][i + (1 << (k - 1))][j]);
        }
      }
    }
  }

  int q = 0;
  std::cin >> q;
  while (q--) {
    int l1 = 0;
    int l2 = 0;
    int r1 = 0;
    int r2 = 0;
    std::cin >> l1 >> r1 >> l2 >> r2;
    l1--;
    r1--;
    int ln1 = l2 - l1;
    ln1 = ln[ln1];
    int ln2 = r2 - r1;
    ln2 = ln[ln2];
    int ans = dp[ln1][ln2][l1][r1];
    ans = std::min(ans, dp[ln1][ln2][l2 - (1 << ln1)][r1]);
    ans = std::min(ans, dp[ln1][ln2][l1][r2 - (1 << ln2)]);
    ans = std::min(ans, dp[ln1][ln2][l2 - (1 << ln1)][r2 - (1 << ln2)]);
    std::cout << ans << '\n';
  }
}
