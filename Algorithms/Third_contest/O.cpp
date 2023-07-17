#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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

  int64_t BFS(int64_t finish) {
    const int64_t k_inf = 1e9;
    std::vector<int64_t> distans(vertex_amount, k_inf);
    std::vector<int64_t> recovery(vertex_amount, -1);
    std::vector<int64_t> recovery_1(vertex_amount, -1);
    distans[0] = 0;
    std::queue<int64_t> q;
    q.push(0);
    while (!q.empty()) {
      int64_t v = q.front();
      q.pop();
      for (const auto& to : graph[v]) {
        if (edges[to].flow_now != edges[to].flow_max || edges[to].flow_now > edges[to].flow_max) {
          if (distans[edges[to].vertex] > distans[v] + 1) {
            recovery[edges[to].vertex] = v;
            recovery_1[edges[to].vertex] = to;
            distans[edges[to].vertex] = distans[v] + 1;
            q.push(edges[to].vertex);
          }
        }
      }
    }
    std::vector<int64_t> ans;
    if (distans[finish] == k_inf) {
      return 0;
    }
    while (finish != -1) {
      ans.push_back(finish);
      finish = recovery[finish];
    }
    std::reverse(ans.begin(), ans.end());
    int64_t min = 10000000000;
    for (size_t i = 1; i < ans.size(); ++i) {
      min = std::min(edges[recovery_1[ans[i]]].flow_max - edges[recovery_1[ans[i]]].flow_now, min);
    }
    for (size_t i = 1; i < ans.size(); ++i) {
      int64_t to = recovery_1[ans[i]];
      edges[to].flow_now += min;
      edges[to ^ 1].flow_now -= min;
    }
    return 1;
  }

  int64_t Answer() {
    int64_t temp = 1;
    while (temp != 0) {
      temp = BFS(vertex_amount - 1);
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
