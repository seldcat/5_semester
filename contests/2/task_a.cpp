// Google style code
#include <iostream>
#include <vector>
#include <numeric>

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

  int GetConnectedComponent(const uint32_t vertex) const {
    std::vector<bool> visited(vertex_count_, false);

    DepthFirstSearch(vertex, visited);

    return std::accumulate(visited.begin(), visited.end(), 0);
  }

 private:
  void DepthFirstSearch(const uint32_t vertex, std::vector<bool> &visited) const {
    visited[vertex] = true;
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (!visited[i] and adjacency_matrix_[vertex][i] == 1) {
        DepthFirstSearch(i, visited);
      }
    }
  }

  std::vector<std::vector<int>> adjacency_matrix_;
  uint32_t vertex_count_;
};

int main() {
    uint32_t n, s;
    std::cin >> n >> s;
    Graph graph(n);
    graph.ReadFromStream(std::cin);
    std::cout << graph.GetConnectedComponent(s-1);
    return 0;
}
