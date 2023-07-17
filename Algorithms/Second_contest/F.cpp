#include <iostream>
#include <vector>
#include <set>
#include <queue>

int16_t BFS(const std::vector<std::vector<std::pair<int16_t, bool>>>& graph, const int16_t& start, int16_t& finish) {
  auto g_size = static_cast<int16_t>(graph.size());
  const int16_t k_inf = 32000;
  std::vector<int16_t> distans(g_size, k_inf);
  distans[start] = 0;
  std::queue<int16_t> q;
  q.push(start);
  while (!q.empty()) {
    int16_t v = q.front();
    q.pop();
    for (const auto& vertex : graph[v]) {
      // if (vertex == std::make_pair(-1, -1)) {
      //   continue;
      // }
      if (distans[vertex.first] > distans[v] + vertex.second) {
        ;
        distans[vertex.first] = distans[v] + vertex.second;
        q.push(vertex.first);
      }
    }
  }
  if (distans[finish] == k_inf) {
    return -1;
  }
  return distans[finish];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int16_t vertex_amount;
  int16_t edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  std::set<std::pair<int16_t, int16_t>> graph;
  int16_t v_1;
  int16_t v_2;
  for (int16_t i = 0; i < edge_amount; ++i) {
    std::cin >> v_1 >> v_2;
    --v_1;
    --v_2;
    graph.insert(std::make_pair(v_1, v_2));
  }
  std::vector<std::vector<std::pair<int16_t, bool>>> graph_new(vertex_amount);
  for (const auto& v : graph) {
    if (graph.count({v.second, v.first})) {
      graph_new[v.first].emplace_back(std::make_pair(v.second, 0));
      graph_new[v.second].emplace_back(std::make_pair(v.first, 0));
    } else {
      graph_new[v.first].emplace_back(std::make_pair(v.second, 0));
      graph_new[v.second].emplace_back(std::make_pair(v.first, 1));
    }
  }
  graph.clear();
  int16_t way_amount;
  std::cin >> way_amount;
  int16_t start;
  int16_t finish;
  for (int16_t i = 0; i < way_amount; ++i) {
    std::cin >> start >> finish;
    --start;
    --finish;
    std::cout << BFS(graph_new, start, finish) << '\n';
  }
  return 0;
}
