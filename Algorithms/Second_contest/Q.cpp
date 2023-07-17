#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void DFS(const std::vector<std::vector<int>>& graph, int vertex, std::vector<int>& used) {
  used[vertex] = 1;
  for (const auto& to : graph[vertex]) {
    if (!used[to]) {
      DFS(graph, to, used);
    }
  }
}

void DFSEulerCycle(std::vector<std::vector<std::pair<int, int>>>& graph, const int& vertex,
                   std::vector<int>& euler_cycle, std::vector<int>& repeat_vertex) {
  for (size_t i = repeat_vertex[vertex]; i < graph[vertex].size(); ++i) {
    if (repeat_vertex[vertex] >= static_cast<int>(graph[vertex].size())) {
      break;
    }
    if (graph[vertex][i].second == 0) {
      ++graph[vertex][i].second;
      ++repeat_vertex[vertex];
      DFSEulerCycle(graph, graph[vertex][i].first, euler_cycle, repeat_vertex);
    }
  }
  euler_cycle.emplace_back(vertex);
}

bool EulerGraph(const std::vector<std::vector<std::pair<int, int>>>& graph,
                const std::vector<std::vector<int>>& simple_graph, int& first) {
  int vertex_amount = static_cast<int>(graph.size()) - 1;
  std::vector<std::vector<int>> inv_graph(vertex_amount + 1);
  for (int i = 1; i < vertex_amount + 1; ++i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      inv_graph[graph[i][j].first].push_back(i);
    }
  }
  std::vector<int> used(vertex_amount + 1, 0);
  bool possible_cycle = true;
  for (int i = 1; i < vertex_amount + 1; ++i) {
    if (simple_graph[i].empty()) {
      used[i] = 1;
    } else {
      if (first == -1) {
        first = i;
      }
    }
    if (graph[i].size() != inv_graph[i].size()) {
      possible_cycle = false;
      break;
    }
  }
  if (first != -1) {
    DFS(simple_graph, first, used);
  } else {
    possible_cycle = false;
  }
  if (possible_cycle) {
    for (int i = 1; i < vertex_amount + 1; ++i) {
      if (!used[i]) {
        possible_cycle = false;
        break;
      }
    }
  }
  return possible_cycle;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int vertex_amount;
  int rote_amount;
  std::cin >> rote_amount >> vertex_amount;
  std::vector<std::vector<std::pair<int, int>>> graph(vertex_amount + 1);
  std::vector<std::vector<int>> simple_graph(vertex_amount + 1);
  for (int i = 0; i < rote_amount; ++i) {
    int len;
    std::cin >> len;
    std::vector<int> temp(len + 1);
    for (int j = 0; j < len + 1; ++j) {
      std::cin >> temp[j];
    }
    for (int j = 0; j < len; ++j) {
      graph[temp[j]].emplace_back(std::make_pair(temp[j + 1], 0));
      simple_graph[temp[j]].emplace_back(temp[j + 1]);
      simple_graph[temp[j + 1]].emplace_back(temp[j]);
    }
  }
  int first = -1;
  bool possible_cycle = EulerGraph(graph, simple_graph, first);
  std::vector<int> euler_cycle;
  if (possible_cycle) {
    std::vector<int> repeat_vertex(vertex_amount + 1);
    DFSEulerCycle(graph, first, euler_cycle, repeat_vertex);
    std::reverse(euler_cycle.begin(), euler_cycle.end());
    std::cout << euler_cycle.size() << ' ';
    for (size_t i = 0; i < euler_cycle.size(); ++i) {
      std::cout << euler_cycle[i] << ' ';
    }
  } else {
    std::cout << 0;
  }
  return 0;
}
