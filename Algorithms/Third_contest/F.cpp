#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Edge {
 public:
  int v_1;
  int v_2;
  int weight;
  Edge() = default;

  Edge(const int& first, const int& second, const int& w) : v_1(first), v_2(second), weight(w) {
  }
};

bool operator<(const Edge& e_1, const Edge& e_2) {
  if (e_1.weight != e_2.weight) {
    return e_1.weight < e_2.weight;
  }
  if (e_1.v_1 != e_2.v_1) {
    return e_1.v_1 < e_2.v_1;
  }
  return e_1.v_2 < e_2.v_2;
}

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<size_t> rank_;
  std::vector<int> weight_;

 public:
  explicit DSU(const int& all) {
    rank_.assign(all, 1);
    weight_.assign(all, 0);
    for (int i = 0; i < all; ++i) {
      parent_.push_back(i);
    }
  }

  int FindSet(const int& vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void Union(int first, int second, const int& weight_edge) {
    first = FindSet(first);
    second = FindSet(second);
    if ((rank_[first] < rank_[second]) && (first != second)) {
      parent_[first] = second;
      rank_[second] += rank_[first];
      weight_[second] += weight_[first] + weight_edge;
    }
    if ((rank_[first] >= rank_[second]) && (first != second)) {
      parent_[second] = first;
      rank_[first] += rank_[second];
      weight_[first] += weight_[second] + weight_edge;
    }
    if (first == second) {
      weight_[first] += weight_edge;
    }
  }

  int GetWaight(const int& vertex) {
    return weight_[FindSet(vertex)];
  }
};

int Kruskal(std::vector<Edge>& graph, DSU& min_ost) {
  std::sort(graph.begin(), graph.end());
  for (auto& to : graph) {
    if (min_ost.FindSet(to.v_1) != min_ost.FindSet(to.v_2)) {
      min_ost.Union(to.v_1, to.v_2, to.weight);
    }
  }
  return min_ost.GetWaight(0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int vertex_amount = 0;
  std::cin >> vertex_amount;
  std::vector<Edge> graph;
  DSU min_ost(vertex_amount + 1);
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      int weight = 0;
      std::cin >> weight;
      graph.emplace_back(i, j, weight);
    }
  }
  for (int i = 0; i < vertex_amount; ++i) {
    int weight = 0;
    std::cin >> weight;
    graph.emplace_back(i, vertex_amount, weight);
  }
  std::cout << Kruskal(graph, min_ost);
  return 0;
}
