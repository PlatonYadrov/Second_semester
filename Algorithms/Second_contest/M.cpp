#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

class Graph {
 public:
  int vertex_amount;
  std::vector<std::vector<int>> graph;
  std::vector<int> tin;
  std::vector<int> tup;
  std::set<int> points;
  int time;
  explicit Graph(int all_vertex) {
    time = 0;
    graph.resize(all_vertex);
    tin.resize(all_vertex, 1e9);
    tup.resize(all_vertex, 1e9);
    vertex_amount = all_vertex;
  }

  void AddEdge(const int& v_1, const int& v_2) {
    graph[v_1].emplace_back(v_2);
    graph[v_2].emplace_back(v_1);
  }

  void Clean() {
    time = 0;
  }

  void DFS(int v, bool root) {
    ++time;
    tin[v] = time;
    tup[v] = tin[v];
    int childs = 0;
    for (const auto& to : graph[v]) {
      if (to == v) {
        continue;
      }
      if (tin[to] == 1e9) {
        ++childs;
        DFS(to, false);
        tup[v] = std::min(tup[v], tup[to]);
        if (!root && tup[to] >= tin[v]) {
          points.insert(v + 1);
        }
      } else {
        tup[v] = std::min(tup[v], tin[to]);
      }
    }
    if (root && childs > 1) {
      points.insert(v + 1);
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
    --v_1;
    --v_2;
    graph.AddEdge(v_1, v_2);
  }
  for (int i = 0; i < vertex_amount; ++i) {
    if (graph.tin[i] == 1e9) {
      graph.Clean();
      graph.DFS(i, true);
    }
  }
  std::cout << graph.points.size() << '\n';
  for (const auto& ans : graph.points) {
    std::cout << ans << '\n';
  }
  return 0;
}
