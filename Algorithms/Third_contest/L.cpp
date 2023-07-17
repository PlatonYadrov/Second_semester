#include <iostream>
#include <vector>
#include <set>

class WeightAndVertex {
 public:
  int weight;
  int16_t vertex;
  WeightAndVertex() : weight(0), vertex(0) {
  }

  WeightAndVertex(const int& new_weight, const int16_t& new_vertex) : weight(new_weight), vertex(new_vertex) {
  }
};

bool operator<(const WeightAndVertex& v_1, const WeightAndVertex& v_2) {
  if (v_1.weight != v_2.weight) {
    return v_1.weight < v_2.weight;
  }
  return v_1.vertex < v_2.vertex;
}

int Dijkstra(const std::vector<std::vector<WeightAndVertex>>& graph, const int16_t& start,
             const std::vector<int>& update) {
  const int k_inf = 1e9;
  std::vector<int> distans(graph.size(), k_inf);
  distans[start] = 0;
  std::set<WeightAndVertex> q;
  q.insert(WeightAndVertex(0, start));
  while (!q.empty()) {
    int16_t v = q.begin()->vertex;
    q.erase(q.begin());
    for (const auto& to : graph[v]) {
      if (distans[to.vertex] > distans[v] + to.weight) {
        q.erase(WeightAndVertex(distans[to.vertex], to.vertex));
        distans[to.vertex] = distans[v] + to.weight;
        q.insert(WeightAndVertex(distans[to.vertex], to.vertex));
      }
    }
  }
  int max = -1;
  for (int i = 0; i < static_cast<int>(update.size()); ++i) {
    if (distans[i] != k_inf && distans[i] + update[i] - update[start] > max) {
      max = distans[i] + update[i] - update[start];
    }
  }
  return max;
}

int Johnson(const int16_t vertex_amount, std::vector<std::vector<WeightAndVertex>>& graph) {
  int max_min_dist = -1;
  std::vector<int> dist(vertex_amount, 0);
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      for (const auto& to : graph[j]) {
        if (dist[to.vertex] > dist[j] + to.weight) {
          dist[to.vertex] = dist[j] + to.weight;
        }
      }
    }
  }
  for (int j = 0; j < vertex_amount; ++j) {
    for (auto& to : graph[j]) {
      to.weight += dist[j] - dist[to.vertex];
    }
  }
  for (int16_t i = 0; i < vertex_amount; ++i) {
    int temp_max = Dijkstra(graph, i, dist);
    if (temp_max > max_min_dist) {
      max_min_dist = temp_max;
    }
  }
  return max_min_dist;
}

int main() {
  int16_t vertex_amount = 0;
  int edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<std::vector<WeightAndVertex>> graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1 = 0;
    int16_t v_2 = 0;
    int weight = 0;
    std::cin >> v_1 >> v_2 >> weight;
    graph[v_1].emplace_back(WeightAndVertex(weight, v_2));
  }
  std::cout << Johnson(vertex_amount, graph);
  return 0;
}
