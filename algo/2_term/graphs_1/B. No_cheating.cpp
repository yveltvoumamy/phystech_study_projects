#include <iostream>
#include <vector>

bool Dfs(int u, int c, int* color, std::vector<std::vector<int>>& adj);

int main() {
  const int maxn = 100;
  std::vector<std::vector<int>> adj(maxn + 1);
  int64_t n, m;
  int color[maxn + 1]{};
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (color[i] == 0 && !Dfs(i, 1, color, adj)) {
      std::cout << "NO" << std::endl;
      return 0;
    }
  }
  std::cout << "YES" << std::endl;
  return 0;
}

bool Dfs(int u, int c, int* color, std::vector<std::vector<int>>& adj) {
  color[u] = c;
  for (int v : adj[u]) {
    if (color[v] == c) {
      return false;
    }
    if (color[v] == 0 && !Dfs(v, -c, color, adj)) {
      return false;
    }
  }
  return true;
}