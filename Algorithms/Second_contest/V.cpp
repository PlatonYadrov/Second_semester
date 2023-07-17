#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Vertex {
 public:
  int used;
  int level;
  int number;
  int x;
  int y;
  Vertex() = default;
  Vertex(int used, int level, int number, int x, int y) {
    this->used = used;
    this->level = level;
    this->number = number;
    this->x = x;
    this->y = y;
  }
};

class Graph {
 public:
  std::vector<Vertex> graph;
  int height;
  int lenght;
  void MakeGraph(const std::vector<std::vector<int>>& table) {
    height = static_cast<int>(table.size());
    lenght = static_cast<int>(table[0].size());
    int number = 0;
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < lenght; ++x) {
        graph.emplace_back(Vertex(0, table[y][x], number, x, y));
        ++number;
      }
    }
  }
  std::vector<bool> visited;
  void BFS(int& count, int first) {
    int i;
    int j;
    std::queue<Vertex> q;
    q.push(graph[first]);
    visited[first] = true;
    int add = 0;
    while (!q.empty()) {
      Vertex v = q.front();
      i = v.number / lenght;
      j = v.number - i * lenght;
      std::vector<Vertex> children;
      if (j >= 1) {
        children.emplace_back(graph[v.number - 1]);
      }
      if (i >= 1) {
        children.emplace_back(graph[v.number - lenght]);
      }
      if (j < lenght - 1) {
        children.emplace_back(graph[v.number + 1]);
      }
      if (i < height - 1) {
        children.emplace_back(graph[v.number + lenght]);
      }
      q.pop();
      for (const auto& child : children) {
        if (graph[child.number].level == v.level && !visited[child.number]) {
          q.push(graph[child.number]);
          visited[child.number] = true;
        }
        if (graph[child.number].level < v.level) {
          ++add;
        }
      }
      if (q.empty() && (add == 0)) {
        ++count;
      }
    }
  }

  int Search() {
    visited.assign(height * lenght, false);
    int count = 0;
    for (int i = 0; i < height * lenght; ++i) {
      if (!visited[i]) {
        BFS(count, i);
      }
    }
    return count;
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  int var;
  std::vector<std::vector<int>> table(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> var;
      table[i].push_back(var);
    }
  }
  Graph graph;
  graph.MakeGraph(table);
  std::cout << graph.Search();
  return 0;
}
