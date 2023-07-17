#include <iostream>
#include <vector>

class Edge {
 public:
  int v_1;
  int v_2;
  int weight;
};

std::istream& operator>>(std::istream& element, Edge& edge) {
  element >> edge.v_1 >> edge.v_2 >> edge.weight;
  --edge.v_1;
  --edge.v_2;
  return element;
}

void FordBalman(const int vertex_amount, const std::vector<Edge>& graph, const int& start) {
  const int k_inf = 30000;
  std::vector<int> dist(vertex_amount, k_inf);
  dist[start] = 0;
  for (int i = 0; i < vertex_amount; ++i) {
    for (const auto& vertex : graph) {
      if (dist[vertex.v_1] != k_inf && dist[vertex.v_2] > dist[vertex.v_1] + vertex.weight) {
        dist[vertex.v_2] = dist[vertex.v_1] + vertex.weight;
      }
    }
  }
  for (const auto& vertex : dist) {
    std::cout << vertex << ' ';
  }
}

int main() {
  int vertex_amount = 0;
  int edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<Edge> graph(edge_amount);
  for (int i = 0; i < edge_amount; ++i) {
    std::cin >> graph[i];
  }
  FordBalman(vertex_amount, graph, 0);
  return 0;
}
