#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<size_t> rank_;

 public:
  explicit DSU(const int& all) {
    rank_.assign(all, 1);
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

  bool Union(int& first, int& second) {
    first = FindSet(first);
    second = FindSet(second);
    if ((rank_[first] < rank_[second]) && (first != second)) {
      parent_[first] = second;
      rank_[second] += rank_[first];
    }
    if ((rank_[first] >= rank_[second]) && (first != second)) {
      parent_[second] = first;
      rank_[first] += rank_[second];
    }
    return (rank_[FindSet(first)] == rank_.size());
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU set(n);
  for (int i = 1; i <= m; ++i) {
    int first = 0;
    int second = 0;
    std::cin >> first >> second;
    if (set.Union(first, second)) {
      std::cout << i;
      break;
    }
  }
  return 0;
}
