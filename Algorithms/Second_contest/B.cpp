#include <iostream>
#include <vector>
#include <queue>

bool BFS(const std::vector<std::vector<int>>& graph, const int& start) {
  auto g_size = static_cast<int>(graph.size());
  std::vector<int> colors(g_size);
  colors[start] = 1;
  std::queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (const auto& vertex : graph[v]) {
      if (colors[vertex] == 0) {
        colors[vertex] = -colors[v];
        q.push(vertex);
      }
      if (colors[v] == colors[vertex]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int vertex_amount;
  int edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<std::vector<int>> graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    --v_1;
    --v_2;
    graph[v_1].push_back(v_2);
    graph[v_2].push_back(v_1);
  }
  bool duo = true;
  for (int i = 0; i < vertex_amount; ++i) {
    if (!BFS(graph, i)) {
      duo = false;
      continue;
    }
  }
  if (duo) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
