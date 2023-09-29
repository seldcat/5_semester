// Google style code
#include <iostream>
#include <queue>
#include <vector>
#include <limits>

class Graph {
 public:
  explicit Graph(uint32_t n, uint32_t k) : adjacency_vectors_(n), vertex_count_(n), exits_count_(k), exits_() {}

  void ReadExits(std::istream& stream) {
    uint32_t vertex;
    for (uint32_t i = 0; i < exits_count_; i++) {
      stream >> vertex;
      exits_.push_back(vertex - 1);
    }
  }

  void ReadFromStream(std::istream& stream) {
    stream >> edges_count_;
    for (uint32_t i = 0; i < edges_count_; i++) {
      int left_vertex;
      int right_vertex;
      stream >> left_vertex >> right_vertex;
      adjacency_vectors_[left_vertex - 1].push_back(right_vertex - 1);
      adjacency_vectors_[right_vertex - 1].push_back(left_vertex - 1);
    }
  }

  std::vector<uint32_t> GetDistances() const {
    return BreadthFirstSearch(exits_);
  }

 private:
  std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& start_vertices) const {
    std::vector<uint32_t> distances(vertex_count_, std::numeric_limits<uint32_t>::max());
    std::queue<uint32_t> queue_vertex;

    for (uint32_t vertex : start_vertices) {   // заполняем очередь начальными вершинами
      distances[vertex] = 0;
      queue_vertex.push(vertex);
    }

    while (!queue_vertex.empty()) {
      uint32_t current_vertex = queue_vertex.front();
      queue_vertex.pop();

      for (auto vertex : adjacency_vectors_[current_vertex]) {
        if (distances[vertex] == std::numeric_limits<uint32_t>::max()) {
          distances[vertex] = distances[current_vertex] + 1;
          queue_vertex.push(vertex);
        }
      }
    }
    return distances;
  }

  std::vector<std::vector<uint32_t>> adjacency_vectors_;
  uint32_t vertex_count_;
  uint32_t exits_count_;
  std::vector<uint32_t> exits_;
  uint32_t edges_count_ {};
};

int main() {
  int n, k;
  std::cin >> n >> k;
  Graph graph(n, k);
  graph.ReadExits(std::cin);
  graph.ReadFromStream(std::cin);


  std::vector<uint32_t> distances = graph.GetDistances();
  for (uint32_t distance : distances) {
    std::cout << distance << ' ';
  }
  std::cout << '\n';

  return 0;
}
