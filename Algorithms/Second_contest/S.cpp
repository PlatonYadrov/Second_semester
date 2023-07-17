#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

class Graph {
 public:
  int vertex_amount;
  std::vector<std::vector<int>> graph;
  std::vector<bool> used;
  std::vector<int> tin;
  std::vector<int> tup;
  std::set<std::pair<int, int>> bridges;
  int bridges_amount;
  int time;
  explicit Graph(int all_vertex) {
    time = 0;
    graph.resize(all_vertex);
    tin.resize(all_vertex);
    tup.resize(all_vertex);
    used.assign(all_vertex, false);
    vertex_amount = all_vertex;
    bridges_amount = 0;
  }

  void AddEdge(int v_1, int v_2) {
    graph[v_1].emplace_back(v_2);
    graph[v_2].emplace_back(v_1);
  }

  void Clean() {
    time = 0;
  }

  void Bridges(int v, int p) {
    used[v] = true;
    tin[v] = time;
    ++time;
    tup[v] = tin[v];
    for (const auto& to : graph[v]) {
      if (to == p) {
        continue;
      }
      if (used[to]) {
        tup[v] = std::min(tup[v], tin[to]);
      } else {
        Bridges(to, v);
        tup[v] = std::min(tup[v], tup[to]);
        if (tup[to] > tin[v]) {
          bridges.insert({std::min(to, v), std::max(to, v)});
        }
      }
    }
  }

  std::vector<int> colors;

  void DFS(const int& vertex, const int& color) {
    colors[vertex] = color;
    for (const auto& to : graph[vertex]) {
      if (colors[to] == -1) {
        DFS(to, color);
      }
    }
  }

  void ComponentsSearch() {
    colors.assign(vertex_amount, -1);
    int components_amount = 0;
    for (int i = 0; i < vertex_amount; ++i) {
      if (colors[i] == -1) {
        DFS(i, components_amount);
        ++components_amount;
      }
    }
  }
};

int main() {
  int vertex_amount;
  int edge_amount;
  std::set<std::pair<int, int>> edges;
  std::cin >> vertex_amount >> edge_amount;
  Graph first_graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    if (v_1 == v_2) {
      continue;
    }
    --v_1;
    --v_2;
    edges.insert({std::min(v_1, v_2), std::max(v_1, v_2)});
    first_graph.AddEdge(v_1, v_2);
  }
  for (int i = 0; i < vertex_amount; ++i) {
    if (!first_graph.used[i]) {
      first_graph.Clean();
      first_graph.Bridges(i, -1);
    }
  }
  for (const auto& bridge : first_graph.bridges) {
    edges.erase(bridge);
  }
  Graph second_graph(vertex_amount);
  for (const auto& edge : edges) {
    second_graph.AddEdge(edge.first, edge.second);
  }
  second_graph.ComponentsSearch();
  std::vector<std::vector<int>> vertex_in_components(second_graph.colors.size());
  for (int i = 0; i < vertex_amount; ++i) {
    vertex_in_components[second_graph.colors[i]].push_back(i);
  }
  std::vector<int> degree(second_graph.colors.size(), 0);
  for (const auto& bridge : first_graph.bridges) {
    for (size_t i = 0; i < second_graph.colors.size(); ++i) {
      degree[i] += std::binary_search(vertex_in_components[i].begin(), vertex_in_components[i].end(), bridge.first);
      degree[i] += std::binary_search(vertex_in_components[i].begin(), vertex_in_components[i].end(), bridge.second);
    }
  }
  int ans = 0;
  for (const auto& d : degree) {
    if (d == 1) {
      ++ans;
    }
  }
  std::cout << (ans + 1) / 2;
  return 0;
}
