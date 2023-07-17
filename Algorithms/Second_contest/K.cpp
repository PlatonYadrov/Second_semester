#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

void DFS(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<int>& used,
         std::vector<int>& parants, std::vector<int>& cycle) {
  used[vertex] = 1;
  for (const auto& to : graph[vertex]) {
    if (used[to] == 0) {
      parants[to] = vertex;
      DFS(graph, to, used, parants, cycle);
      if (!cycle.empty()) {
        return;
      }
    } else if (used[to] == 1) {
      parants[to] = vertex;
      cycle = {to};
      for (int i = parants[to]; i != to; i = parants[i]) {
        cycle.push_back(i);
      }
      std::reverse(cycle.begin(), cycle.end());
      return;
    }
  }
  used[vertex] = 2;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int amount;
  std::cin >> amount;
  std::vector<std::string> color_graph(amount, "");
  for (int i = 0; i < amount - 1; ++i) {
    std::string s;
    std::cin >> s;
    color_graph[i] = s;
  }
  std::vector<std::vector<int>> graph(amount);
  for (int v_1 = 0; v_1 < amount; ++v_1) {
    int v_2 = v_1 + 1;
    for (const auto& s : color_graph[v_1]) {
      if (s == 'R') {
        graph[v_1].push_back(v_2);
      } else {
        graph[v_2].push_back(v_1);
      }
      ++v_2;
    }
  }
  // int count = 0;
  // for (const auto& gr : graph) {
  //   std::cout << count << ": ";
  //   ++count;
  //   for (const auto& v : gr) {
  //     std::cout << v << ' ';
  //   }
  //   std::cout << '\n';
  // }
  std::vector<int> used(amount);
  std::vector<int> parants(amount, -1);
  std::vector<int> cycle;
  for (int i = 0; (i < amount) && cycle.empty(); ++i) {
    if (used[i] == 0) {
      DFS(graph, i, used, parants, cycle);
    }
  }
  if (cycle.empty()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
