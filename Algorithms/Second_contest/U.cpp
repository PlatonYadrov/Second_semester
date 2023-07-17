#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

void DFS(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<int>& used, const int& from,
         bool& cycle) {
  used[vertex] = 1;
  for (const auto& to : graph[vertex]) {
    if (to == from) {
      continue;
    }
    if (used[to] == 0) {
      DFS(graph, to, used, vertex, cycle);
    } else if (used[to] == 1) {
      cycle = true;
    }
  }
  used[vertex] = 2;
}

int main() {
  int vertex_amount;
  int edge_amount;
  std::cin >> vertex_amount >> edge_amount;
  std::string subsequence;
  std::vector<std::vector<int>> graph(vertex_amount);
  std::vector<int> used(vertex_amount);
  bool cycle = false;
  std::cin >> subsequence;
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    std::cin >> v_1 >> v_2;
    if (v_1 == v_2) {
      std::cout << "NO";
      return 0;
    }
    --v_1;
    --v_2;
    graph[v_1].emplace_back(v_2);
    graph[v_2].emplace_back(v_1);
  }
  DFS(graph, 0, used, -1, cycle);
  if (cycle || (std::find(used.begin(), used.end(), 0) != used.end())) {
    std::cout << "NO";
  } else {
    bool alcan = true;
    for (int i = 0; i < vertex_amount; ++i) {
      if (subsequence[i] == 'H') {
        if (!((graph[i].size() == 1) && (subsequence[graph[i][0]] == 'C'))) {
          alcan = false;
          break;
        }
      } else {
        if (graph[i].size() == 4) {
          std::set<int> temp;
          for (const auto& tmp : graph[i]) {
            temp.insert(tmp);
          }
          if (temp.size() != 4) {
            alcan = false;
            break;
          }
        } else {
          alcan = false;
          break;
        }
      }
    }
    if (alcan) {
      std::cout << "YES";
    } else {
      std::cout << "NO";
    }
  }
  return 0;
}
