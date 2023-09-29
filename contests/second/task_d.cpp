// Google style code
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

class Graph {
 public:
  explicit Graph(uint32_t n, uint32_t m) : vertex_count_(n), edges_count_(m), adjacency_matrix_(n, std::vector<bool>(n, false)) {}
  
  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < edges_count_; i++) {
      uint32_t left_vertex;
      uint32_t right_vertex;
      stream >> left_vertex >> right_vertex;
      adjacency_matrix_[left_vertex - 1][right_vertex - 1] = true;
    }
  }
  
  bool HasCycle() const {
    std::vector<bool> visited(vertex_count_, false);
    std::vector<bool> left(vertex_count_, false);
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (DepthFirstSearchForHasCycle(i, visited, left)) {
        return true;
      }
    }
    return false;
  }
  
  std::vector<uint32_t> TopologicalSort() const {
    std::vector<uint32_t> answer;
    std::vector<bool> visited(vertex_count_, false);
    
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (!visited[i]) {
        DepthFirstSearchForTopologicalSort(i, answer, visited);
      }
    }
    std::reverse(std::begin(answer), std::end(answer));
    return answer;
  }
    
 private:
  void DepthFirstSearchForTopologicalSort(uint32_t vertex, std::vector<uint32_t>& answer, std::vector<bool>& visited) const {
    visited[vertex] = true;
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (adjacency_matrix_[vertex][i] && !visited[i]) {
        DepthFirstSearchForTopologicalSort(i, answer, visited);
      }
    }
    answer.push_back(vertex);
  }
  
  bool DepthFirstSearchForHasCycle(const int vertex, std::vector<bool>& visited, std::vector<bool>& left) const {
    if (visited[vertex] && left[vertex]) {    // мы уже прошли эту вершину
      return false;
    }
    if (!visited[vertex]) {
      visited[vertex] = true;
    }

    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (adjacency_matrix_[vertex][i]) {
        if (visited[i] && !left[i]) {
          return true;
        }
        if (!visited[i] && DepthFirstSearchForHasCycle(i, visited, left)) {
          return true;
        }
      }
    }
    left[vertex] = true;
    return false;
  }
    
  uint32_t vertex_count_;
  uint32_t edges_count_;
  std::vector<std::vector<bool>> adjacency_matrix_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n, m);
  graph.ReadFromStream(std::cin);
  if (!graph.HasCycle()) {
    std::cout << "Yes" << '\n';
    std::vector<uint32_t> answer = graph.TopologicalSort();
    for (uint32_t vertex : answer) {
      std::cout << vertex + 1 << ' ';
    }
  } else {
    std::cout << "No";
  }
  std::cout << '\n';
  return 0;
}
