// Google style code
#include <iostream>
#include <vector>
#include <cmath>

class Graph {
 public:
  explicit Graph(uint32_t n) : adjacency_matrix_(n, std::vector<uint32_t>(n, 0)), vertex_count_(n) {}
  ~Graph() {}
  
  void ReadFromStream(std::istream& stream) {
    std::vector<std::vector<uint32_t>> points(vertex_count_, std::vector<uint32_t>(2, 0));
    for (uint32_t i = 0; i < vertex_count_; i++) {
      stream >> points[i][0] >> points[i][1];
    }
    
    for (uint32_t i = 0; i < vertex_count_;  i++) {
      for (uint32_t j = 0; j < i; j++) {
        uint32_t distance = std::sqrt(std::pow(points[i][0] - points[j][0], 2) + std::pow(points[i][1] - points[j][1], 2));
        adjacency_matrix_[i][j] = distance;
        adjacency_matrix_[j][i] = distance;
      }
    }
    
    uint32_t special_count;
    stream >> special_count;
    for (int i = 0; i < special_count; i++) {
      uint32_t u, v, distance;
      stream >> u >> v >> distance;
      adjacency_matrix_[u][v] = distance;
    }
  }
  
 private:
  std::vector<std::vector<uint32_t>> adjacency_matrix_;
  uint32_t vertex_count_;
}
