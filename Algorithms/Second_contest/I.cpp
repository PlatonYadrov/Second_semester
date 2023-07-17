#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void DFS(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<int>& used, const int& color) {
  used[vertex] = color;
  for (const auto& to : graph[vertex]) {
    if (used[to] == -1) {
      DFS(graph, to, used, color);
    }
  }
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
  int components_amount = 0;
  std::vector<int> used(vertex_amount, -1);
  for (int i = 0; i < vertex_amount; ++i) {
    if (used[i] == -1) {
      DFS(graph, i, used, components_amount);
      ++components_amount;
    }
  }
  std::vector<std::vector<int>> vertex_in_components(components_amount);
  for (int i = 0; i < vertex_amount; ++i) {
    vertex_in_components[used[i]].push_back(i);
  }
  std::cout << components_amount << '\n';
  for (int i = 0; i < components_amount; ++i) {
    std::cout << vertex_in_components[i].size() << '\n';
    for (const auto& vertex : vertex_in_components[i]) {
      std::cout << vertex + 1 << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
