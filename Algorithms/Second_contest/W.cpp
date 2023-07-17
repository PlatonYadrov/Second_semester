#include <iostream>
#include <vector>
#include <string>
#include <map>

void DFS(const std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph, std::pair<int64_t, int64_t> v,
         int64_t parent, std::vector<bool>& used, std::vector<std::pair<int64_t, int64_t>>& vertex) {
  used[v.first] = true;
  if (v.first != 2) {
    vertex[v.first] = std::make_pair(v.second - vertex[parent].first, -vertex[parent].second);
  }
  for (const auto& to : graph[v.first]) {
    if (!used[to.first]) {
      DFS(graph, to, v.first, used, vertex);
    }
  }
}

void RecoveryGraph(const std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>>& lines,
                   const std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph, int64_t& best,
                   std::vector<std::pair<int64_t, int64_t>>& vertex) {
  int vertex_amount = static_cast<int>(graph.size()) - 1;
  std::vector<bool> used(vertex_amount + 1, false);
  vertex[2] = std::make_pair(0, 1);
  DFS(graph, graph[2][0], 2, used, vertex);
  int64_t first_option = 1e7;
  int64_t first = 1e7;
  int64_t second_option = 1e7;
  int64_t second = 1e7;
  for (int64_t i = 1; i < vertex_amount + 1; ++i) {
    if (vertex[i].second == -1) {
      if (first > vertex[i].first) {
        first = vertex[i].first;
        first_option = vertex[i].first - 1;
      }
    } else {
      if (second > vertex[i].first) {
        second = vertex[i].first;
        second_option = 1 - vertex[i].first;
      }
    }
  }
  std::vector<int> answer(vertex_amount + 1);
  used.assign(vertex_amount + 1, false);
  best = second_option;
  bool flag = false;
  for (int i = 1; i < vertex_amount + 1; ++i) {
    answer[i] = vertex[i].first + vertex[i].second * best;
    if (used[answer[i]] || (1 > answer[i]) || (answer[i] > vertex_amount)) {
      flag = true;
      break;
    }
    used[answer[i]] = true;
  }
  for (const auto& line : lines) {
    int64_t temp_1 = answer[line.first.first];
    int64_t temp_2 = answer[line.first.second];
    if ((temp_1 + temp_2 != line.second) || flag) {
      best = first_option;
      break;
    }
  }
}

int main() {
  int64_t vertex_amount;
  int64_t edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>> lines;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(vertex_amount + 1);
  std::vector<std::pair<int64_t, int64_t>> vertex(vertex_amount + 1);
  for (int64_t i = 0; i < edge_amount; ++i) {
    int64_t v_1;
    int64_t v_2;
    int64_t weight;
    std::cin >> v_1 >> v_2 >> weight;
    lines.emplace_back(std::make_pair(std::make_pair(std::min(v_1, v_2), std::max(v_1, v_2)), weight));
    graph[v_1].emplace_back(std::make_pair(v_2, weight));
    graph[v_2].emplace_back(std::make_pair(v_1, weight));
  }
  int64_t best;
  RecoveryGraph(lines, graph, best, vertex);
  for (const auto& v : vertex) {
    if (v == *(vertex.begin())) {
      continue;
    }
    std::cout << v.first + v.second * best << ' ';
  }
  return 0;
}
