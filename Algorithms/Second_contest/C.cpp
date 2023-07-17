#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int Increase(const int& var) {
  if (var / 1000 != 9) {
    return 1000 + var;
  }
  return var;
}

int Reduce(const int& var) {
  if (var % 10 != 1) {
    return var - 1;
  }
  return var;
}

int CircleLeft(const int& var) {
  return (var % 1000) * 10 + var / 1000;
}

int CircleRight(const int& var) {
  return (var % 10) * 1000 + var / 10;
}

void BFS(const int& start, int& finish) {
  std::vector<bool> used(10000, false);
  std::vector<int> recovery(10000, -1);
  std::queue<int> q;
  used[start] = true;
  q.push(start);
  std::vector<int> children;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == finish) {
      break;
    }
    children = {Increase(v), Reduce(v), CircleLeft(v), CircleRight(v)};
    for (const auto& child : children) {
      if (!used[child]) {
        used[child] = true;
        q.push(child);
        recovery[child] = v;
      }
    }
  }
  std::vector<int> ans;
  while (finish != -1) {
    ans.push_back(finish);
    finish = recovery[finish];
  }
  std::reverse(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (const auto& a : ans) {
    std::cout << a << '\n';
  }
}

int main() {
  int start;
  int finish;
  std::cin >> start >> finish;
  BFS(start, finish);
  return 0;
}
