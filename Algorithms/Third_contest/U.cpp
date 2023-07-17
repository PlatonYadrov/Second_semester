#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

template <>
struct std::hash<std::pair<int, int>> {
  std::size_t operator()(std::pair<int, int> const& a) const noexcept {
    auto hasher = std::hash<int>{};
    int hash = static_cast<int>(hasher(a.first)) + static_cast<int>(hasher(a.second));
    return hash;
  }
};

bool FloydWarshall(const int& vertex_amount, std::vector<std::vector<int>>& distans,
                   std::vector<std::vector<int>>& parents, const std::vector<int>& trip,
                   std::unordered_map<std::pair<int, int>, int>& names) {
  const int k_inf = 1e9;
  for (int vertex = 0; vertex < vertex_amount; ++vertex) {
    for (int v_1 = 0; v_1 < vertex_amount; ++v_1) {
      for (int v_2 = 0; v_2 < vertex_amount; ++v_2) {
        if (distans[v_1][vertex] != k_inf && distans[vertex][v_2] != k_inf &&
            distans[v_1][v_2] > distans[v_1][vertex] + distans[vertex][v_2]) {
          distans[v_1][v_2] = distans[v_1][vertex] + distans[vertex][v_2];
          parents[v_1][v_2] = parents[v_1][vertex];
        }
      }
    }
  }
  std::vector<int> answer;
  for (size_t i = 0; i < trip.size() - 1; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      if (distans[j][j] < 0 && distans[j][trip[i + 1]] != k_inf && distans[trip[i]][j] != k_inf) {
        return true;
      }
    }
    for (int v = trip[i]; v != trip[i + 1]; v = parents[v][trip[i + 1]]) {
      answer.push_back(names[std::pair(v, parents[v][trip[i + 1]])]);
    }
  }
  std::cout << answer.size() << '\n';
  for (const auto& to : answer) {
    std::cout << to << ' ';
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const int k_inf = 1e9;
  int vertex_amount = 0;
  int edge_amount = 0;
  int lecture_amount = 0;
  std::cin >> vertex_amount >> edge_amount >> lecture_amount;
  std::vector<int> trip(lecture_amount);
  trip.shrink_to_fit();
  std::vector<std::vector<int>> graph(vertex_amount, std::vector<int>(vertex_amount, k_inf));
  for (auto& to : graph) {
    to.shrink_to_fit();
  }
  graph.shrink_to_fit();
  std::vector<std::vector<int>> parents(vertex_amount, std::vector<int>(vertex_amount, -1));
  for (auto& to : parents) {
    to.shrink_to_fit();
  }
  parents.shrink_to_fit();
  std::unordered_map<std::pair<int, int>, int> names(edge_amount);
  for (int i = 0; i < vertex_amount; ++i) {
    graph[i][i] = 0;
  }
  for (int i = 0; i < edge_amount; ++i) {
    int v_1 = 0;
    int v_2 = 0;
    int weight = 0;
    std::cin >> v_1 >> v_2 >> weight;
    --v_1;
    --v_2;
    weight = -weight;
    graph[v_1][v_2] = weight;
    parents[v_1][v_2] = v_2;
    names[std::pair(v_1, v_2)] = i + 1;
  }
  for (int i = 0; i < lecture_amount; ++i) {
    std::cin >> trip[i];
    --trip[i];
  }
  if (FloydWarshall(vertex_amount, graph, parents, trip, names)) {
    std::cout << "infinitely kind";
  }
  return 0;
}
