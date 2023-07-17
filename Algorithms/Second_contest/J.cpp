#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void GetCycle(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<int>& used,
              std::vector<int>& parants, std::vector<int>& cycle) {
  used[vertex] = 1;
  for (const auto& to : graph[vertex]) {
    if (used[to] == 0) {
      parants[to] = vertex;
      GetCycle(graph, to, used, parants, cycle);
      if (!cycle.empty()) {
        return;
      }
    } else if (used[to] == 1) {
      parants[to] = vertex;
      cycle = {to};
      for (int i = parants[to]; i != to; i = parants[i]) {
        cycle.push_back(i);
      }
      std::reverse(cycle.begin(), cycle.end());
      return;
    }
  }
  used[vertex] = 2;
}

void DFS(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<bool>& used,
         std::vector<int>& answer) {
  used[vertex] = true;
  for (const auto& to : graph[vertex]) {
    if (!used[to]) {
      DFS(graph, to, used, answer);
    }
  }
  answer.push_back(vertex);
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
  }
  std::vector<int> used(vertex_amount);
  std::vector<int> parants(vertex_amount, -1);
  std::vector<int> cycle;
  for (int i = 0; (i < vertex_amount) && cycle.empty(); ++i) {
    if (used[i] == 0) {
      GetCycle(graph, i, used, parants, cycle);
    }
  }
  if (!cycle.empty()) {
    std::cout << -1;
  } else {
    std::vector<bool> visited(vertex_amount, false);
    std::vector<int> answer(vertex_amount);
    for (int i = 0; i < vertex_amount; ++i) {
      if (!visited[i]) {
        DFS(graph, i, visited, answer);
      }
    }
    std::reverse(answer.begin(), answer.end());
    for (int i = 0; i < vertex_amount; ++i) {
      std::cout << answer[i] + 1 << ' ';
    }
  }
  return 0;
}
