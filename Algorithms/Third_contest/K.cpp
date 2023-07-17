#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Edge {
 public:
  int v_1;
  int v_2;
  int weight;
  Edge() = default;

  Edge(const int& first, const int& second, const int& w) : v_1(first), v_2(second), weight(w) {
  }
};

void FordBalman(const int vertex_amount, const std::vector<Edge>& graph) {
  const int k_inf = 1000000000;
  std::vector<int> dist(vertex_amount, 0);
  std::vector<int> parents(vertex_amount, -1);
  for (int i = 0; i < vertex_amount - 1; ++i) {
    for (const auto& vertex : graph) {
      if (dist[vertex.v_1] != k_inf && dist[vertex.v_2] > dist[vertex.v_1] + vertex.weight) {
        dist[vertex.v_2] = std::max(dist[vertex.v_1] + vertex.weight, -k_inf);
        parents[vertex.v_2] = vertex.v_1;
      }
    }
  }
  for (auto vertex : graph) {
    if (dist[vertex.v_1] != k_inf && dist[vertex.v_2] > dist[vertex.v_1] + vertex.weight) {
      parents[vertex.v_2] = vertex.v_1;
      for (int i = 0; i < vertex_amount; ++i) {
        vertex.v_2 = parents[vertex.v_2];
      }
      int last = vertex.v_2;
      std::vector<int> cycle = {last};
      for (int vertex = parents[last]; vertex != last; vertex = parents[vertex]) {
        cycle.push_back(vertex);
      }
      std::reverse(cycle.begin(), cycle.end());
      if (!cycle.empty()) {
        std::cout << "YES" << '\n';
        std::cout << cycle.size() + 1 << '\n';
        for (const auto& vertex : cycle) {
          std::cout << vertex + 1 << ' ';
        }
        std::cout << cycle[0] + 1;
      } else {
        std::cout << "NO";
      }
      return;
    }
  }
  std::cout << "NO";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int vertex_amount = 0;
  std::cin >> vertex_amount;
  std::vector<Edge> graph(vertex_amount);
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight == 100000) {
        continue;
      }
      Edge temp(i, j, weight);
      graph.emplace_back(temp);
    }
  }
  FordBalman(vertex_amount, graph);
  return 0;
}
