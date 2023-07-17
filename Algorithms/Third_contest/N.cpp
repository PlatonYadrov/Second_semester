#include <iostream>
#include <vector>

class Edge {
 public:
  int64_t vertex;
  int64_t flow_now;
  int64_t flow_max;
  Edge(int64_t v, int64_t flow, int64_t flow_max) : vertex(v), flow_now(flow), flow_max(flow_max) {
  }

  Edge() = default;
};

class Graph {
 public:
  int64_t vertex_amount;
  std::vector<std::vector<int64_t>> graph;
  std::vector<Edge> edges;
  std::vector<int64_t> used;

  explicit Graph(int64_t all) {
    vertex_amount = all;
    graph.resize(vertex_amount);
    used.resize(vertex_amount);
  }

  int64_t DFS(const int64_t& vertex, int64_t min, int64_t& iteration) {
    if (vertex == vertex_amount - 1) {
      return min;
    }
    used[vertex] = iteration;
    for (int64_t to : graph[vertex]) {
      if (edges[to].flow_now != edges[to].flow_max) {
        if (used[edges[to].vertex] != iteration) {
          min = std::min(min, edges[to].flow_max - edges[to].flow_now);
          int64_t update = DFS(edges[to].vertex, min, iteration);
          if (update > 0) {
            edges[to].flow_now += update;
            edges[to ^ 1].flow_now -= update;
            return update;
          }
        }
      }
    }
    return 0;
  }

  int64_t Answer() {
    int64_t temp = 1;
    int64_t iteration = 1;
    while (temp != 0) {
      temp = DFS(0, 1000000000, iteration);
      ++iteration;
    }
    int64_t ans = 0;
    for (int64_t to : graph[0]) {
      ans += edges[to].flow_now;
    }
    return ans;
  }
};

int main() {
  int64_t vertex_amount = 0;
  int64_t edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  Graph graph(vertex_amount);
  for (int64_t i = 0; i < edge_amount; ++i) {
    int64_t v_1 = 0;
    int64_t v_2 = 0;
    int64_t flow_max = 0;
    std::cin >> v_1 >> v_2 >> flow_max;
    --v_1;
    --v_2;
    graph.graph[v_1].push_back(i * 2);
    graph.graph[v_2].push_back(i * 2 + 1);
    Edge temp_1(v_2, 0, flow_max);
    graph.edges.emplace_back(temp_1);
    Edge temp_2(v_1, 0, 0);
    graph.edges.emplace_back(temp_2);
  }
  std::cout << graph.Answer();
  return 0;
}
