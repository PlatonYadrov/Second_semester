#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class WeightAndVertex {
 public:
  int weight;
  int vertex;
  WeightAndVertex() : weight(0), vertex(0) {
  }

  WeightAndVertex(int new_weight, int new_vertex) : weight(new_weight), vertex(new_vertex) {
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
  int max = 1000000;
  int vertex_finish = 0;
  int up = 0;
  int down = 0;
  int teleports_amount = 0;
  int teleport_in = 0;
  int teleport_out = 0;
  std::cin >> vertex_finish >> up >> down;
  --vertex_finish;
  std::cin >> teleport_in >> teleport_out >> teleports_amount;
  std::vector<std::vector<WeightAndVertex>> graph(max + teleports_amount);
  int max_vertex = vertex_finish;
  for (int i = max; i < teleports_amount + max; ++i) {
    int all = 0;
    std::cin >> all;
    for (int j = 0; j < all; ++j) {
      int vertex = 0;
      std::cin >> vertex;
      --vertex;
      max_vertex = std::max(max_vertex, vertex);
      WeightAndVertex temp_1(teleport_out, vertex);
      graph[i].emplace_back(temp_1);
      WeightAndVertex temp_2(teleport_in, i);
      graph[vertex].emplace_back(temp_2);
    }
  }
  for (int i = 0; i < max_vertex; ++i) {
    graph[i].emplace_back(up, i + 1);
    graph[i + 1].emplace_back(down, i);
  }
  std::cout << Dijkstra(graph, 0, vertex_finish);
}
