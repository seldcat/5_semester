// Google style code
#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 public:
  explicit Graph(uint32_t n) : adjacency_matrix_(n, std::vector<int>(n, 0)), vertex_count_(n){}

  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < vertex_count_; i++) {
      for (uint32_t j = 0; j < vertex_count_; j++) {
        stream >> adjacency_matrix_[i][j];
      }
    }
  }

  const std::vector<std::vector<int>> FloydAlgorithm() const {
    std::vector<std::vector<int>> shortest_distances = adjacency_matrix_;
    
    for (uint32_t i = 0; i < vertex_count_; i++) {
      for (uint32_t vertex_u = 0; vertex_u < vertex_count_; vertex_u++) {
        for (uint32_t vertex_v = 0; vertex_v < vertex_count_; vertex_v++) {
          if (vertex_u != vertex_v && vertex_u != i && i != vertex_v) {
            shortest_distances[vertex_u][vertex_v] = std::min(shortest_distances[vertex_u][vertex_v], shortest_distances[vertex_u][i] + shortest_distances[i][vertex_v]);
          }
        }
      }
    }
    
    return shortest_distances;
  }

 private:
  std::vector<std::vector<int>> adjacency_matrix_;
  uint32_t vertex_count_;
};

int main() {
  uint32_t n;
  std::cin >> n;
  Graph graph(n);
  graph.ReadFromStream(std::cin);
  const std::vector<std::vector<int>> shortest_distances = graph.FloydAlgorithm();
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      std::cout << shortest_distances[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}