#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Edge {
 public:
  int64_t v_1;
  int64_t v_2;
  int64_t weight;
  Edge() = default;

  Edge(const int64_t& first, const int64_t& second, const int64_t& w) : v_1(first), v_2(second), weight(w) {
  }

  Edge(const Edge& other) {
    v_1 = other.v_1;
    v_2 = other.v_2;
    weight = other.weight;
  }

  Edge& operator=(const Edge& other) = default;
};

bool operator==(const Edge& a, const Edge& b) {
  return ((a.v_1 == b.v_1) && (a.v_2 == b.v_2) && (a.weight == b.weight));
}

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
  std::vector<int64_t> parent_;
  std::vector<size_t> rank_;
  std::vector<int64_t> weight_;

 public:
  int64_t size;
  std::vector<Edge> min;
  explicit DSU(const int64_t& all) {
    rank_.assign(all, 1);
    weight_.assign(all, 0);
    for (int64_t i = 0; i < all; ++i) {
      parent_.push_back(i);
    }
    min.assign(all, Edge(10, 10, 1000000001));
    size = all;
  }

  int64_t FindSet(const int64_t& vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void Union(int64_t first, int64_t second, const int64_t& weight_edge) {
    first = FindSet(first);
    second = FindSet(second);
    --size;
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

  int64_t GetWaight(const int64_t& vertex) {
    return weight_[FindSet(vertex)];
  }

  int64_t Size() {
    return size;
  }
};

int64_t Boruvka(int64_t vertex_amount, std::vector<Edge>& graph, DSU& min_ost) {
  while (min_ost.Size() > 1) {
    min_ost.min.assign(vertex_amount, Edge(10, 10, 1000000001));
    for (auto& to : graph) {
      int64_t component_1 = min_ost.FindSet(to.v_1);
      int64_t component_2 = min_ost.FindSet(to.v_2);
      if (component_1 != component_2) {
        if (to.weight < min_ost.min[component_1].weight) {
          min_ost.min[component_1] = to;
        }
        if (to.weight < min_ost.min[component_2].weight) {
          min_ost.min[component_2] = to;
        }
      }
    }
    std::set<Edge> min;
    for (auto& to : min_ost.min) {
      min.insert(to);
    }
    for (auto& to : min) {
      if (to == Edge(10, 10, 1000000001)) {
        continue;
      }
      min_ost.Union(to.v_1, to.v_2, to.weight);
    }
  }
  return min_ost.GetWaight(0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t vertex_amount = 0;
  int64_t edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<Edge> graph(edge_amount);
  DSU min_ost(vertex_amount);
  for (int64_t i = 0; i < edge_amount; ++i) {
    int64_t v_1 = 0;
    int64_t v_2 = 0;
    int64_t weight = 0;
    std::cin >> v_1 >> v_2 >> weight;
    --v_1;
    --v_2;
    graph.emplace_back(v_1, v_2, weight);
  }
  std::cout << Boruvka(vertex_amount, graph, min_ost);
  return 0;
}
