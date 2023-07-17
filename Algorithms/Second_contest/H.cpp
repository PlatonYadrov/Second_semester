#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void DFS(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<bool>& used) {
  used[vertex] = true;
  for (const auto& to : graph[vertex]) {
    if (!used[to]) {
      DFS(graph, to, used);
    }
  }
}

int main() {
  int amount;
  std::cin >> amount;
  std::vector<std::vector<int>> graph(amount);
  for (int i = 0; i < amount; ++i) {
    int v;
    std::cin >> v;
    --v;
    graph[i].push_back(v);
    graph[v].push_back(i);
  }
  int ans = 0;
  std::vector<bool> used(amount, false);
  for (int i = 0; i < amount; ++i) {
    if (!used[i]) {
      DFS(graph, i, used);
      ++ans;
    }
  }
  std::cout << ans;
  return 0;
}
