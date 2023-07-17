#include <iostream>
#include <vector>

void FloydWarshall(const int& vertex_amount, std::vector<std::vector<int>>& distans) {
  for (int vertex = 0; vertex < vertex_amount; ++vertex) {
    for (int v_1 = 0; v_1 < vertex_amount; ++v_1) {
      for (int v_2 = 0; v_2 < vertex_amount; ++v_2) {
        if (distans[v_1][v_2] > distans[v_1][vertex] + distans[vertex][v_2]) {
          distans[v_1][v_2] = distans[v_1][vertex] + distans[vertex][v_2];
        }
      }
    }
  }
}

int main() {
  int vertex_amount = 0;
  std::cin >> vertex_amount;
  std::vector<std::vector<int>> graph(vertex_amount, std::vector<int>(vertex_amount));
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      std::cin >> graph[i][j];
    }
  }
  FloydWarshall(vertex_amount, graph);
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      std::cout << graph[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
