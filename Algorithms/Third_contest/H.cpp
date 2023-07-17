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

int FordBalman(const int vertex_amount, const std::vector<Edge>& graph, const int& start, const int& finish,
               const int& all_nights) {
  const int k_inf = 1000000000;
  std::vector<int> dist(vertex_amount, k_inf);
  dist[start] = 0;
  for (int i = 0; i < std::min(all_nights, vertex_amount); ++i) {
    std::vector<int> temp(vertex_amount, -1);
    for (const auto& vertex : graph) {
      if (dist[vertex.v_1] != k_inf && dist[vertex.v_2] > dist[vertex.v_1] + vertex.weight) {
        temp[vertex.v_2] = dist[vertex.v_1] + vertex.weight;
      }
    }
    for (int j = 0; j < vertex_amount; ++j) {
      if (temp[j] != -1) {
        dist[j] = temp[j];
      }
    }
  }
  if (dist[finish] == k_inf) {
    return -1;
  }
  return dist[finish];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int vertex_amount = 0;
  int edge_amount = 0;
  int all_nights = 0;
  int start = 0;
  int finish = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::cin >> all_nights >> start >> finish;
  --start;
  --finish;
  std::vector<Edge> graph(edge_amount);
  for (int i = 0; i < edge_amount; ++i) {
    std::cin >> graph[i];
  }
  std::cout << FordBalman(vertex_amount, graph, start, finish, all_nights);
  return 0;
}
