#include <iostream>
#include <vector>
#include <set>

class WeightAndVertex {
 public:
  int64_t weight;
  int64_t vertex;
  WeightAndVertex() : weight(0), vertex(0) {
  }

  WeightAndVertex(const int64_t& new_weight, const int64_t& new_vertex) : weight(new_weight), vertex(new_vertex) {
  }
};

bool operator<(const WeightAndVertex& v_1, const WeightAndVertex& v_2) {
  if (v_1.weight != v_2.weight) {
    return v_1.weight < v_2.weight;
  }
  return v_1.vertex < v_2.vertex;
}

int64_t Dijkstra(const std::vector<std::vector<WeightAndVertex>>& graph, const int64_t& start, const int64_t& finish,
                 const std::vector<int64_t>& infected) {
  const int64_t k_inf = 1e10;
  std::vector<int64_t> distans(graph.size(), k_inf);
  distans[start] = 0;
  std::set<WeightAndVertex> q;
  q.insert(WeightAndVertex(0, start));
  while (!q.empty()) {
    int64_t v = q.begin()->vertex;
    q.erase(q.begin());
    for (const auto& to : graph[v]) {
      if (distans[to.vertex] > distans[v] + to.weight) {
        q.erase(WeightAndVertex(distans[to.vertex], to.vertex));
        distans[to.vertex] = distans[v] + to.weight;
        q.insert(WeightAndVertex(distans[to.vertex], to.vertex));
      }
    }
  }
  int64_t min_dist = distans[finish];
  for (const auto& to : infected) {
    if (min_dist >= distans[to]) {
      return -1;
    }
  }
  return min_dist;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t vertex_amount = 0;
  int64_t edge_amount = 0;
  int64_t infected_amount = 0;
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> vertex_amount >> edge_amount >> infected_amount;
  std::vector<int64_t> infected(infected_amount);
  for (int64_t i = 0; i < infected_amount; ++i) {
    std::cin >> infected[i];
    --infected[i];
  }
  std::vector<std::vector<WeightAndVertex>> graph(vertex_amount);
  for (int64_t i = 0; i < edge_amount; ++i) {
    int64_t v_1 = 0;
    int64_t v_2 = 0;
    int64_t weight = 0;
    std::cin >> v_1 >> v_2 >> weight;
    --v_1;
    --v_2;
    graph[v_1].emplace_back(WeightAndVertex(weight, v_2));
    graph[v_2].emplace_back(WeightAndVertex(weight, v_1));
  }
  std::cin >> start >> finish;
  --start;
  --finish;
  std::cout << Dijkstra(graph, finish, start, infected);
  return 0;
}
