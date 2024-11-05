#include <iostream>
#include <queue>
#include <vector>

void Bfs(bool* visited, int* parent, int* dist, int a, std::vector<std::vector<int>>& adj);

int main() {
  const int maxn = 50006;
  std::vector<std::vector<int>> adj(maxn);
  int n, m, a, b;
  int dist[maxn];
  int parent[maxn];
  bool visited[maxn];
  std::cin >> n >> m;
  std::cin >> a >> b;
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Bfs(visited, parent, dist, a, adj);
  if (!visited[b]) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << dist[b] << std::endl;
    std::vector<int> path;
    int u = b;
    while (u != a) {
      path.push_back(u);
      u = parent[u];
    }
    path.push_back(a);
    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i] << " ";
    }
  }

  return 0;
}

void Bfs(bool* visited, int* parent, int* dist, int a, std::vector<std::vector<int>>& adj) {
  std::queue<int> q;
  q.push(a);
  visited[a] = true;
  dist[a] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      if (!visited[v]) {
        visited[v] = true;
        q.push(v);
        dist[v] = dist[u] + 1;
        parent[v] = u;
      }
    }
  }
}