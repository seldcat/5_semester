#include <iostream>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(uint32_t n): array_(n), tree_(n, 0), vertex_count_(n) {
    ReadFromStream(std::cin);
    for (uint32_t i = 0; i < vertex_count_; i++) {
      ModifyTree(i, array_[i]);
    }
  }
  
  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < vertex_count_; ++i) {
      stream >> array_[i];
    }
  }
  
  void Update(uint32_t vertex, int64_t new_value) {
    int64_t delta = new_value - array_[vertex - 1];
    array_[vertex - 1] = new_value;
    ModifyTree(vertex - 1, delta);
  }
  
  int64_t GetSum(uint32_t left, uint32_t right) {
    return GetSum(right) - GetSum(left - 1);
  }
    
 private:
  void ModifyTree(uint32_t vertex, int64_t value) {
    for (; vertex < vertex_count_; vertex = vertex | (vertex + 1)) {
      tree_[vertex] += value;
    }
  }
  
  int64_t GetSum(int64_t right) {
    int64_t result = 0;
    right--;
    for (; right >= 0; right = (right & (right + 1)) - 1) {
      result += tree_[right];
    }
    return result;
  }
  
  std::vector<uint64_t> array_;
  std::vector<int64_t> tree_;
  uint32_t vertex_count_;
};

int main() {
  uint32_t n;
  std::cin >> n;

  FenwickTree fenwick_tree(n);

  uint32_t m;
  std::cin >> m;

  char command;
  uint32_t arg1, arg2;

  for (uint32_t i = 0; i < m; i++) {
    std::cin >> command >> arg1 >> arg2;
    switch (command) {
    case 'u':
      fenwick_tree.Update(arg1, arg2);
      break;
    case 's':
      std::cout << fenwick_tree.GetSum(arg1, arg2) << ' ';
      break;
    default: break;
    }
    // segment_tree.WriteToStream(std::cout);
  }

  return 0;
}
