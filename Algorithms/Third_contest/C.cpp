#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

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

class Graph {
 public:
  std::vector<std::vector<WeightAndVertex>> graph;
  int vertex_amount;
  explicit Graph(const int& all) {
    vertex_amount = all;
    graph.resize(all);
  }

  int Prim() {
    const int k_inf = 1000000000;
    std::vector<bool> used(vertex_amount, false);
    std::vector<int> distans(vertex_amount, k_inf);
    distans[0] = 0;
    std::set<WeightAndVertex> q;
    q.insert(WeightAndVertex(0, 0));
    while (!q.empty()) {
      int v = q.begin()->vertex;
      q.erase(q.begin());
      for (const auto& to : graph[v]) {
        if (!used[to.vertex]) {
          if (distans[to.vertex] > to.weight) {
            distans[to.vertex] = to.weight;
            q.insert(to);
          }
        }
      }
      used[v] = true;
    }
    int answer = 0;
    for (const auto& dist : distans) {
      answer += dist;
    }
    return answer;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int vertex_amount = 0;
  int edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  Graph graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1 = 0;
    int v_2 = 0;
    int weight = 0;
    std::cin >> v_1 >> v_2 >> weight;
    --v_1;
    --v_2;
    graph.graph[v_1].emplace_back(weight, v_2);
    graph.graph[v_2].emplace_back(weight, v_1);
  }
  std::cout << graph.Prim();
  return 0;
}
