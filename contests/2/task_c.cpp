// Google style code
#include <iostream>
#include <vector>

class Graph {
 public:
   explicit Graph(int n) : adjacency_matrix_(n, std::vector<bool>(n, false)), vertex_count_(n) {}
  
  void ReadFromStream(std::istream& stream) {
    for (int i = 0; i < vertex_count_; i++) {
      for (int j = 0; j < vertex_count_; j++) {
        int edge;
        stream >> edge;
        adjacency_matrix_[i][j] = edge == 1;
      }
    }
  }
  
  bool HasCycle() const {
    std::vector<bool> visited(vertex_count_, false);
    std::vector<bool> left(vertex_count_, false);
    for (int i = 0; i < vertex_count_; i++) {
      if (DepthFirstSearch(i, visited, left)) {
        return true;
      }
    }
    return false;
  }
  
 private:
  bool DepthFirstSearch(const int vertex, std::vector<bool>& visited, std::vector<bool>& left) const {
    if (visited[vertex] && left[vertex]) {    // мы уже прошли эту вершину
      return false;
    }
    if (!visited[vertex]) {
      visited[vertex] = true;
    }
    
    for (int i = 0; i < vertex_count_; i++) {
      if (adjacency_matrix_[vertex][i]) {
        if (visited[i] && !left[i]) {
          return true;
        }
        if (!visited[i] && DepthFirstSearch(i, visited, left)) {
          return true;
        }
      }
    }
    left[vertex] = true;
    return false;
  }
  
  std::vector<std::vector<bool>> adjacency_matrix_;
  int vertex_count_;
};

int main() {
  int n;
  std::cin >> n;
  Graph graph(n);
  graph.ReadFromStream(std::cin);
  if (graph.HasCycle()) {
    std::cout << 1;
  } else {
    std::cout << 0;
  }
  std::cout << '\n';
  return 0;
}