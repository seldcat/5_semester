// Google style code
#include <iostream>
#include <vector>
#include <numeric>

class Graph {
 public:
  explicit Graph(uint32_t n) : adjacency_matrix_(n, std::vector<int>(n, 0)), count_vertex_(n){}

  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < count_vertex_; i++) {
      for (uint32_t j = 0; j < count_vertex_; j++) {
        stream >> adjacency_matrix_[i][j];
      }
    }
  }

  int GetConnectedComponent(const uint32_t vertex) const {
    std::vector<bool> visited(count_vertex_, false);

    DepthFirstSearch(vertex, visited);

    return std::accumulate(visited.begin(), visited.end(), 0);
  }

 private:
  void DepthFirstSearch(const uint32_t vertex, std::vector<bool> &visited) const {
    visited[vertex] = true;
    for (uint32_t i = 0; i < count_vertex_; i++) {
      if (!visited[i] and adjacency_matrix_[vertex][i] == 1) {
        DepthFirstSearch(i, visited);
      }
    }
  }

  std::vector<std::vector<int>> adjacency_matrix_;
  uint32_t count_vertex_;
};

int main() {
    uint32_t n, s;
    std::cin >> n >> s;
    Graph graph(n);
    graph.ReadFromStream(std::cin);
    std::cout << graph.GetConnectedComponent(s-1);
    return 0;
}
