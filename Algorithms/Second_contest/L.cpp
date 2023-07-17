#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Graph {
 private:
  int vertex_amount_;
  int components_amount_;
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> inv_graph_;
  std::vector<int> used_;
  std::vector<int> order_;

 public:
  void Used(int vertex) {
    used_[vertex] = 1;
    for (const auto& to : inv_graph_[vertex]) {
      if (!used_[to]) {
        Used(to);
      }
    }
    order_.push_back(vertex);
  }

  void Colors(int vertex, int color) {
    used_[vertex] = color;
    for (const auto& to : graph_[vertex]) {
      if (!used_[to]) {
        Colors(to, color);
      }
    }
    order_.push_back(vertex);
  }

  explicit Graph(int all_vertex) {
    graph_.resize(all_vertex);
    inv_graph_.resize(all_vertex);
    vertex_amount_ = all_vertex;
  }

  void AddEdge(int v_1, int v_2) {
    graph_[v_1].push_back(v_2);
    inv_graph_[v_2].push_back(v_1);
  }

  std::vector<int> FindComponents() {
    used_.assign(vertex_amount_, 0);
    for (int i = 0; i < vertex_amount_; ++i) {
      if (!used_[i]) {
        Used(i);
      }
    }
    std::reverse(order_.begin(), order_.end());
    used_.assign(vertex_amount_, 0);
    components_amount_ = 0;
    for (int i = 0; i < vertex_amount_; ++i) {
      if (!used_[order_[i]]) {
        ++components_amount_;
        Colors(order_[i], components_amount_);
      }
    }
    return used_;
  }

  int GetComponentsAmount() {
    return components_amount_;
  }
};

int main() {
  int vertex_amount;
  int edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  Graph graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    --v_1;
    --v_2;
    graph.AddEdge(v_1, v_2);
  }
  std::vector<int> answer = graph.FindComponents();
  std::vector<int> help(graph.GetComponentsAmount() + 1);
  for (int i = 1; i < graph.GetComponentsAmount() + 1; ++i) {
    help[i] = graph.GetComponentsAmount() + 1 - i;
  }
  std::cout << graph.GetComponentsAmount() << '\n';
  for (const auto& ans : answer) {
    std::cout << help[ans] << ' ';
  }
  return 0;
}
