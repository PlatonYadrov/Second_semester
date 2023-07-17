#include <iostream>
#include <vector>
#include <set>
#include <queue>

class WeightAndVertex {
 public:
  int weight;
  int vertex;
  WeightAndVertex() : weight(0), vertex(0) {
  }

  WeightAndVertex(const int& new_weight, const int& new_vertex) : weight(new_weight), vertex(new_vertex) {
  }
};

bool operator<(const WeightAndVertex& v_1, const WeightAndVertex& v_2) {
  if (v_1.weight != v_2.weight) {
    return v_1.weight < v_2.weight;
  }
  return v_1.vertex < v_2.vertex;
}

int Dijkstra(const std::vector<std::vector<WeightAndVertex>>& graph, const int& start, const int& finish) {
  const int k_inf = 1e9;
  std::vector<int> distans(graph.size(), k_inf);
  distans[start] = 0;
  std::priority_queue<WeightAndVertex> q;
  q.push(WeightAndVertex(0, start));
  while (!q.empty()) {
    int v = q.top().vertex;
    q.pop();
    if (v == finish) {
      break;
    }
    for (const auto& to : graph[v]) {
      if (distans[to.vertex] > distans[v] + to.weight) {
        distans[to.vertex] = distans[v] + to.weight;
        q.push(WeightAndVertex(-distans[to.vertex], to.vertex));
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
  int vertex_amount = 0;
  int start = 0;
  int finish = 0;
  std::cin >> vertex_amount;
  std::vector<std::vector<WeightAndVertex>> graph(vertex_amount);
  std::cin >> start >> finish;
  --start;
  --finish;
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight < 1) {
        continue;
      }
      graph[i].emplace_back(WeightAndVertex(weight, j));
    }
  }
  std::cout << Dijkstra(graph, start, finish);
  return 0;
}
