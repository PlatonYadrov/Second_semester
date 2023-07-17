#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void BFS(const std::vector<std::vector<int>>& graph, const int& start, int& finish, const int& g_size) {
  const int k_inf = 1e9;
  std::vector<int> distans(g_size, k_inf);
  std::vector<int> recovery(g_size, -1);
  distans[start] = 0;
  std::queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (const auto& vertex : graph[v]) {
      if (distans[vertex] > distans[v] + 1) {
        recovery[vertex] = v;
        distans[vertex] = distans[v] + 1;
        q.push(vertex);
      }
    }
  }
  std::vector<int> ans;
  if (distans[finish] == k_inf) {
    std::cout << -1;
    return;
  }
  while (finish != -1) {
    ans.push_back(finish);
    finish = recovery[finish];
  }
  std::reverse(ans.begin(), ans.end());
  std::cout << ans.size() - 1 << '\n';
  for (const auto& a : ans) {
    std::cout << a + 1 << ' ';
  }
}

int main() {
  int vertex_amount;
  int edge_amount;
  int start;
  int finish;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<std::vector<int>> graph(vertex_amount);
  std::cin >> start >> finish;
  --start;
  --finish;
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    --v_1;
    --v_2;
    graph[v_1].push_back(v_2);
    graph[v_2].push_back(v_1);
  }
  BFS(graph, start, finish, vertex_amount);
  return 0;
}
