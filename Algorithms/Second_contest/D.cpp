#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Graph {
 public:
  std::vector<bool> used;
  std::vector<int16_t> distans;
  std::queue<int> q;
  int height;
  int lenght;
  void MakeGraph(const int& n, const int& m) {
    height = n;
    lenght = m;
    bool var;
    for (int num = 0; num < static_cast<int>(n) * static_cast<int>(m); ++num) {
      std::cin >> var;
      used.emplace_back(false);
      if (var) {
        q.push(num);
        distans.emplace_back(0);
      } else {
        distans.emplace_back(32000);
      }
    }
  }

  void BFS() {
    int i;
    int j;
    while (!q.empty()) {
      int v = q.front();
      i = v / lenght;
      j = v - i * lenght;
      q.pop();
      std::vector<int> children;
      if (j >= 1) {
        children.emplace_back(v - 1);
      }
      if (i >= 1) {
        children.emplace_back(v - lenght);
      }
      if (j < lenght - 1) {
        children.emplace_back(v + 1);
      }
      if (i < height - 1) {
        children.emplace_back(v + lenght);
      }
      for (auto& to : children) {
        if (!used[to]) {
          used[to] = true;
          if (distans[v] + 1 < distans[to]) {
            distans[to] = distans[v] + 1;
          }
          q.push(to);
        }
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph;
  graph.MakeGraph(n, m);
  graph.BFS();
  int number = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << graph.distans[number] << ' ';
      ++number;
    }
    std::cout << '\n';
  }
  return 0;
}
