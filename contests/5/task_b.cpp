#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
 public:
   SegmentTree(uint32_t n): vertex_count_(n), array_(n), tree_(4 * n, 0) {
     ReadFromStream(std::cin);
     Build(1, 0, vertex_count_ - 1);
  }
  
  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < vertex_count_; ++i) {
      stream >> array_[i];
    }
  }
  
  void WriteToStream(std::ostream& stream) const {
    for (uint32_t i = 0; i < 4 * vertex_count_; i++) {
      stream << tree_[i] << " ";
    }
  }
  
  uint64_t GetSum(uint32_t left, uint32_t right) const {
    return Query(1, 0, vertex_count_ - 1, left - 1, right - 1);
  }
  
  void Update(uint32_t position, uint64_t new_value) {
    Updater(1, 0, vertex_count_ - 1, position - 1, new_value);
  }
 private:
  void Build(uint32_t vertex, uint32_t left_border, uint32_t right_border) {
    if (left_border == right_border) {
      tree_[vertex] = array_[left_border];   // если у нас один элемент на отрезке, то его индекс и берем
      return;
    }
    uint32_t middle_border = (left_border + right_border) / 2;
    Build(2 * vertex, left_border, middle_border);
    Build(2 * vertex + 1, middle_border + 1, right_border);
    tree_[vertex] = tree_[2 * vertex] + tree_[2 * vertex + 1];
  }

  uint64_t Query(uint32_t vertex, uint32_t left_border, uint32_t right_border, uint32_t left, uint32_t right) const {
    if (left > right) {
      return 0;
    }
    if (left == left_border && right == right_border) {
      return tree_[vertex];
    }
    uint32_t middle_border = (left_border + right_border) / 2;
    return Query(vertex * 2, left_border, middle_border, left, std::min(right, middle_border))
                + Query(vertex * 2 + 1, middle_border + 1, right_border, std::max(left, middle_border + 1), right);
  }

  void Updater(uint32_t vertex, uint32_t left_border, uint32_t right_border, uint32_t position, uint64_t new_value) {
    if (left_border == right_border) {
      tree_[vertex] = new_value;
      return;
    }
    uint32_t middle_border = (left_border + right_border) / 2;
    if (position <= middle_border) {
      Updater(vertex * 2, left_border, middle_border, position, new_value);
    } else {
      Updater(vertex * 2 + 1, middle_border + 1, right_border, position, new_value);
    }
    tree_[vertex] = tree_[vertex * 2] + tree_[vertex * 2 + 1];
  }
    
   
  uint32_t vertex_count_;
  std::vector<uint64_t> array_;
  std::vector<uint64_t> tree_;
};

int main() {
  uint32_t n;
  std::cin >> n;
  
  SegmentTree segment_tree(n);
  
  uint32_t m;
  std::cin >> m;
  
  char command;
  uint32_t arg1, arg2;

  for (uint32_t i = 0; i < m; i++) {
    std::cin >> command >> arg1 >> arg2;
    switch (command) {
      case 'u':
        segment_tree.Update(arg1, arg2);
        break;
      case 's':
        std::cout << segment_tree.GetSum(arg1, arg2) << ' ';
        break;
      default: break;
    }
    // segment_tree.WriteToStream(std::cout);
  }

  return 0;
}
