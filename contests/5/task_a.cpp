#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
 public:
  SegmentTree(uint32_t n): array_(n), size_(n), tree_(4 * n, std::numeric_limits<uint32_t>::max()) {
     ReadFromStream(std::cin);
     Build(1, 0, size_ - 1);
  }
  
  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < size_; ++i) {
      stream >> array_[i];
    }
  }

  void WriteToStream(std::ostream& stream) const {
    for (uint32_t i = 0; i < 4 * size_; i++) {
      stream << tree_[i] << " ";
    }
  }

  uint32_t FindMaxIndex(uint32_t left, uint32_t right) const {
    return Query(1, 0, size_ - 1, left - 1, right - 1) + 1;
  }
  
 private:
  uint32_t GetMaxIndex(uint32_t a, uint32_t b) const {
    return (array_[a] > array_[b]) ? a : b;
  }

  void Build(uint32_t vertex, uint32_t left_border, uint32_t right_border) {
    if (left_border == right_border) {
      tree_[vertex] = left_border;   // если у нас один элемент на отрезке, то его индекс и берем
    } else {
      uint32_t middle_border = (left_border + right_border) / 2;
      Build(2 * vertex, left_border, middle_border);
      Build(2 * vertex + 1, middle_border + 1, right_border);
      tree_[vertex] = GetMaxIndex(tree_[2 * vertex], tree_[2 * vertex + 1]);
    }
  }

  uint32_t Query(uint32_t vertex, uint32_t left_border, uint32_t right_border, uint32_t left, uint32_t right) const {
    if (left > right) {
      return std::numeric_limits<uint32_t>::max();
    }
    if (left == left_border && right == right_border) {
      return tree_[vertex];
    }
    uint32_t middle_border = (left_border + right_border) / 2;
    uint32_t left_max_index = Query(2 * vertex, left_border, middle_border, left, std::min(right, middle_border));
    uint32_t right_max_index = Query(2 * vertex + 1, middle_border + 1, right_border, std::max(left, middle_border + 1), right);
    if (left_max_index == std::numeric_limits<uint32_t>::max()) {
      return right_max_index;
    }
    if (right_max_index == std::numeric_limits<uint32_t>::max()) {
      return left_max_index;
    }
    return GetMaxIndex(left_max_index, right_max_index);
  }
  
  std::vector<uint32_t> array_;
  uint32_t size_;
  std::vector<uint32_t> tree_;
};

int main() {
  uint32_t N;
  std::cin >> N;

  SegmentTree segment_tree(N);
  
  //segment_tree.WriteToStream(std::cout);

  uint32_t K;
  std::cin >> K;

  for (uint32_t i = 0; i < K; ++i) {
    uint32_t left, right;
    std::cin >> left >> right;
    uint32_t max_index = segment_tree.FindMaxIndex(left, right);
    std::cout << max_index << " ";
  }

  return 0;
}
