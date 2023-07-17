#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<size_t> rank_;
  std::vector<int> weight_;

 public:
  explicit DSU(const int& all) {
    rank_.assign(all, 1);
    weight_.assign(all, 0);
    for (int i = 0; i < all; ++i) {
      parent_.push_back(i);
    }
  }

  int FindSet(const int& vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void Union(int& first, int& second, const int& weight_edge) {
    first = FindSet(first);
    second = FindSet(second);
    if ((rank_[first] < rank_[second]) && (first != second)) {
      parent_[first] = second;
      rank_[second] += rank_[first];
      weight_[second] += weight_[first] + weight_edge;
    }
    if ((rank_[first] >= rank_[second]) && (first != second)) {
      parent_[second] = first;
      rank_[first] += rank_[second];
      weight_[first] += weight_[second] + weight_edge;
    }
    if (first == second) {
      weight_[first] += weight_edge;
    }
  }

  int GetWaight(const int& vertex) {
    return weight_[FindSet(vertex)];
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU set(n);
  for (int i = 0; i < m; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 2) {
      int vertex = 0;
      std::cin >> vertex;
      --vertex;
      std::cout << set.GetWaight(vertex) << '\n';
    } else {
      int first = 0;
      int second = 0;
      int weight = 0;
      std::cin >> first >> second >> weight;
      --first;
      --second;
      set.Union(first, second, weight);
    }
  }
  return 0;
}
