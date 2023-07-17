#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
 public:
  int64_t v_1;
  int64_t v_2;
  int64_t tin;
  int64_t tup;

  Edge() : v_1(0), v_2(0), tin(0), tup(0) {
  }

  Edge(const int64_t& v_1, const int64_t& v_2, const int64_t& tin, const int64_t& tup)
      : v_1(v_1), v_2(v_2), tin(tin), tup(tup) {
  }
};

std::istream& operator>>(std::istream& element, Edge& edge) {
  element >> edge.v_1 >> edge.tin >> edge.v_2 >> edge.tup;
  --edge.v_1;
  --edge.v_2;
  return element;
}

bool operator<(const Edge& e_1, const Edge& e_2) {
  if (e_1.tin != e_2.tin) {
    return e_1.tin > e_2.tin;
  }
  if (e_1.v_1 != e_2.v_1) {
    return e_1.v_1 < e_2.v_1;
  }
  if (e_1.v_2 != e_2.v_2) {
    return e_1.v_2 < e_2.v_2;
  }
  return e_1.tup < e_2.tup;
}

int64_t FordBalman(const int64_t& vertex_amount, std::vector<Edge>& graph, const int64_t& start,
                   const int64_t& finish) {
  std::sort(graph.begin(), graph.end());
  const int64_t k_inf = 1e18;
  std::vector<int64_t> dist(vertex_amount, k_inf);
  dist[start] = 0;
  for (int64_t vertex = 0; vertex < vertex_amount; ++vertex) {
    for (const auto& to : graph) {
      if (dist[to.v_1] != k_inf && dist[to.v_2] > to.tup && dist[to.v_1] <= to.tin) {
        dist[to.v_2] = to.tup;
      }
    }
  }
  return dist[finish];
}

int main() {
  int64_t vertex_amount = 0;
  int64_t start = 0;
  int64_t finish = 0;
  int64_t edge_amount = 0;
  std::cin >> vertex_amount;
  std::cin >> start >> finish;
  --start;
  --finish;
  std::cin >> edge_amount;
  std::vector<Edge> graph(edge_amount);
  for (int64_t i = 0; i < edge_amount; ++i) {
    std::cin >> graph[i];
  }
  std::cout << FordBalman(vertex_amount, graph, start, finish);
  return 0;
}
