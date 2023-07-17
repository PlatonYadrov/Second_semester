#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

class Edge {
 public:
  int vertex;
  int flow_now;
  int flow_max;
  Edge(int v, int flow, int flow_max) : vertex(v), flow_now(flow), flow_max(flow_max) {
  }

  Edge() = default;
};

class Graph {
 public:
  int vertex_amount;
  std::vector<std::vector<int>> graph;
  std::vector<Edge> edges;
  std::vector<int> used;

  explicit Graph(int all) {
    vertex_amount = all;
    graph.resize(vertex_amount);
    used.resize(vertex_amount);
  }

  int BFS(int finish) {
    const int k_inf = 1e9;
    std::vector<int> distans(vertex_amount, k_inf);
    std::vector<int> recovery(vertex_amount, -1);
    std::vector<int> recovery_1(vertex_amount, -1);
    distans[0] = 0;
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (const auto& to : graph[v]) {
        if (edges[to].flow_now != edges[to].flow_max || edges[to].flow_now > edges[to].flow_max) {
          if (distans[edges[to].vertex] > distans[v] + 1) {
            recovery[edges[to].vertex] = v;
            recovery_1[edges[to].vertex] = to;
            distans[edges[to].vertex] = distans[v] + 1;
            q.push(edges[to].vertex);
          }
        }
      }
    }
    std::vector<int> ans;
    if (distans[finish] == k_inf) {
      return 0;
    }
    while (finish != -1) {
      ans.push_back(finish);
      finish = recovery[finish];
    }
    std::reverse(ans.begin(), ans.end());
    int min = 100000;
    for (size_t i = 1; i < ans.size(); ++i) {
      min = std::min(edges[recovery_1[ans[i]]].flow_max - edges[recovery_1[ans[i]]].flow_now, min);
    }
    if (min <= 0) {
      return 0;
    }
    for (size_t i = 1; i < ans.size(); ++i) {
      int to = recovery_1[ans[i]];
      edges[to].flow_now += min;
      edges[to ^ 1].flow_now -= min;
    }
    return 1;
  }

  bool Check() {
    int temp = 1;
    while (temp != 0) {
      temp = BFS(vertex_amount - 1);
    }
    int input = 0;
    for (int to : graph[0]) {
      input += edges[to].flow_now;
      if (edges[to].flow_now != edges[to].flow_max) {
        return false;
      }
    }
    int output = 0;
    for (int to : graph[vertex_amount - 1]) {
      output += edges[to ^ 1].flow_now;
      if (edges[to ^ 1].flow_now != edges[to ^ 1].flow_max) {
        return false;
      }
    }
    return (input == output);
  }
};

int main() {
  int len = 0;
  int height = 0;
  std::cin >> height >> len;
  std::vector<std::string> input(height);
  for (int i = 0; i < height; ++i) {
    std::cin >> input[i];
  }
  Graph graph(len * height + 2);
  int count = 0;
  int not_points = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < len; ++j) {
      char symbol = input[i][j];
      int valence = 0;
      if (symbol == 'H') {
        valence = 1;
      } else if (symbol == 'O') {
        valence = 2;
      } else if (symbol == 'N') {
        valence = 3;
      } else if (symbol == 'C') {
        valence = 4;
      } else {
        continue;
      }
      ++not_points;
      if ((i + j) % 2 == 0) {
        graph.graph[0].push_back(count);
        graph.graph[i * len + j + 1].push_back(count + 1);
        count += 2;
        Edge temp_1(i * len + j + 1, 0, valence);
        graph.edges.emplace_back(temp_1);
        Edge temp_2(0, 0, 0);
        graph.edges.emplace_back(temp_2);
        if (j != 0 && input[i][j - 1] != '.') {
          graph.graph[i * len + j + 1].push_back(count);
          graph.graph[i * len + j].push_back(count + 1);
          count += 2;
          graph.edges.emplace_back(i * len + j, 0, 1);
          graph.edges.emplace_back(i * len + j + 1, 0, 0);
        }
        if (j != len - 1 && input[i][j + 1] != '.') {
          graph.graph[i * len + j + 1].push_back(count);
          graph.graph[i * len + j + 2].push_back(count + 1);
          count += 2;
          graph.edges.emplace_back(i * len + j + 2, 0, 1);
          graph.edges.emplace_back(i * len + j + 1, 0, 0);
        }
        if (i != 0 && input[i - 1][j] != '.') {
          graph.graph[i * len + j + 1].push_back(count);
          graph.graph[i * len + j + 1 - len].push_back(count + 1);
          count += 2;
          graph.edges.emplace_back(i * len + j + 1 - len, 0, 1);
          graph.edges.emplace_back(i * len + j + 1, 0, 0);
        }
        if (i != height - 1 && input[i + 1][j] != '.') {
          graph.graph[i * len + j + 1].push_back(count);
          graph.graph[i * len + j + 1 + len].push_back(count + 1);
          count += 2;
          graph.edges.emplace_back(i * len + j + 1 + len, 0, 1);
          graph.edges.emplace_back(i * len + j + 1, 0, 0);
        }
      } else {
        graph.graph[i * len + j + 1].push_back(count);
        graph.graph[len * height + 1].push_back(count + 1);
        count += 2;
        graph.edges.emplace_back(len * height + 1, 0, valence);
        graph.edges.emplace_back(i * len + j + 1, 0, 0);
      }
    }
  }
  if (graph.Check() && not_points != 0) {
    std::cout << "Valid";
  } else {
    std::cout << "Invalid";
  }
}
