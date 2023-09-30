// Google style code
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

class Graph {
 public:
  explicit Graph(uint32_t n) : adjacency_matrix_(n, std::vector<double>(n, 0)), vertex_count_(n) {}
  ~Graph() {}
  
  void ReadFromStream(std::istream& stream) {
    std::vector<std::vector<double>> points(vertex_count_, std::vector<double>(2, 0));   // координаты каждой точки
    for (uint32_t i = 0; i < vertex_count_; i++) {
      stream >> points[i][0] >> points[i][1];
    }
    
    // заполняем матрицу смежности
    for (uint32_t i = 0; i < vertex_count_;  i++) {
      for (uint32_t j = 0; j < i; j++) {
        double distance = std::sqrt(std::pow(points[i][0] - points[j][0], 2) + std::pow(points[i][1] - points[j][1], 2));
        adjacency_matrix_[i][j] = distance;
        adjacency_matrix_[j][i] = distance;
      }
    }

    // особые пары
    uint32_t special_count;
    stream >> special_count;
    for (uint32_t i = 0; i < special_count; i++) {
      uint32_t u, v, distance;
      stream >> u >> v >> distance;
      adjacency_matrix_[u - 1][v - 1] = distance;
    }

    // номера городов А и Б
    uint32_t temp;
    stream >> temp;
    point_a_ = temp - 1;
    stream >> temp;
    point_b_ = temp - 1;
  }

  double GetShortestDistance() {
    std::vector<double> distances = AlgorithmDijkstra(point_a_);
    return distances[point_b_];
  }

 private:
  std::vector<double> AlgorithmDijkstra(uint32_t vertex) {
    std::vector<double> distances(vertex_count_, std::numeric_limits<double>::max());
    distances[vertex] = 0;
    std::vector<bool> used(vertex_count_, false);

    for (uint32_t i = 0; i < vertex_count_; i++) {
      uint32_t min_vertex = std::numeric_limits<uint32_t>::max();   // вершина с минимальным расстоянием от вершины vertex
      for (uint32_t j = 0; j < vertex_count_; j++) {
        if (!used[j] && (min_vertex == std::numeric_limits<uint32_t>::max() || distances[j] < distances[min_vertex])) {
          min_vertex = j;
        }
      }

      if (min_vertex == std::numeric_limits<uint32_t>::max()) {
        break;
      }

      used[min_vertex] = true;
      // обновляем вектор distances в связи с нахождением вершины с мин расстоянием
      for (uint32_t j = 0; j < vertex_count_; j++) {
        if (distances[min_vertex] + adjacency_matrix_[min_vertex][j] < distances[j]) {
          distances[j] = distances[min_vertex] + adjacency_matrix_[min_vertex][j];
        }
      }
    }
    return distances;
  }

  std::vector<std::vector<double>> adjacency_matrix_;
  uint32_t vertex_count_;
  uint32_t point_a_ {}, point_b_ {};
};

int main() {
  uint32_t n;
  std::cin >> n;
  Graph graph(n);
  graph.ReadFromStream(std::cin);
  std::cout << graph.GetShortestDistance() << '\n';
  return 0;
}
