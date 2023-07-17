#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

class Trio {
 public:
  int v_1;
  int v_2;
  int number;
  Trio(int v_1, int v_2, int number) {
    this->v_1 = v_1;
    this->v_2 = v_2;
    this->number = number;
  }
};

class Graph {
 public:
  int vertex_amount;
  std::vector<std::vector<int>> graph;
  std::vector<std::pair<int, int>> edges;
  std::vector<int> tin;
  std::vector<int> tup;
  std::vector<int> bridges;
  int bridges_amount;
  int time;
  explicit Graph(int all_vertex) {
    time = 0;
    graph.resize(all_vertex);
    tin.resize(all_vertex, 1e9);
    tup.resize(all_vertex, 1e9);
    vertex_amount = all_vertex;
    bridges_amount = 0;
  }

  void AddEdge(const Trio& edge) {
    edges.emplace_back(std::make_pair(std::min(edge.v_1, edge.v_2), std::max(edge.v_1, edge.v_2)));
    graph[edge.v_1].emplace_back(edge.number);
    graph[edge.v_2].emplace_back(edge.number);
  }

  void Clean() {
    time = 0;
  }

  void DFS(int v, int p) {
    tin[v] = time;
    ++time;
    tup[v] = tin[v];
    for (const auto& edge_id : graph[v]) {
      if (edge_id == p) {
        continue;
      }
      auto& edge = edges[edge_id];
      int to = edge.first == v ? edge.second : edge.first;
      if (to == v) {
        continue;
      }
      if (tin[to] != 1e9) {
        tup[v] = std::min(tup[v], tin[to]);
      } else {
        DFS(to, edge_id);
        tup[v] = std::min(tup[v], tup[to]);
      }
      if (tup[to] > tin[v]) {
        bridges.push_back(edge_id + 1);
      }
    }
  }
};

int main() {
  int vertex_amount;
  int edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  Graph graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    if (v_1 == v_2) {
      continue;
    }
    --v_1;
    --v_2;
    graph.AddEdge(Trio(v_1, v_2, i));
  }
  for (int i = 0; i < vertex_amount; ++i) {
    if (graph.tin[i] == 1e9) {
      graph.Clean();
      graph.DFS(i, 1e9);
    }
  }
  std::sort(graph.bridges.begin(), graph.bridges.end());
  std::cout << graph.bridges.size() << '\n';
  for (const auto& ans : graph.bridges) {
    std::cout << ans << '\n';
  }
  return 0;
}
