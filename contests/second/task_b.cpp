// Google style code
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Graph {
 public:
  explicit Graph(uint32_t n, uint32_t k) : adjacency_vectors_(n, std::vector<uint32_t>()), count_vertex_(n), count_edges_(0), count_exits_(k), vector_exits_() {}
   
  void PutCountEdges(uint32_t n) {
    count_edges_ = n;
  }

  void ReadExits(std::istream& stream) {
    uint32_t vertex;
    for (uint32_t i = 0; i < count_exits_; i++) {
      stream >> vertex;
      vector_exits_.push_back(vertex - 1);
    }
  }

  void ReadFromStream(std::istream& stream) {
    int left_vertex, right_vertex;
    for (uint32_t i = 0; i < count_edges_; i++) {
      stream >> left_vertex >> right_vertex;
      adjacency_vectors_[left_vertex - 1].push_back(right_vertex - 1);
      adjacency_vectors_[right_vertex - 1].push_back(left_vertex - 1);
    }
  }

  std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& start_vertices) const {
    bool is_there_only_visited_vertex = std::find(start_vertices.begin(), start_vertices.end(), UINT32_MAX) == std::end(start_vertices);
    if (is_there_only_visited_vertex) {    // когда непосещенных вершин нет, мы закончили bfs
      return start_vertices;
    }

    bool are_there_any_exits = std::find(start_vertices.begin(), start_vertices.end(), 0) != std::end(start_vertices);
    std::vector<uint32_t> next_vertices = start_vertices;
    if (not are_there_any_exits) {    // если нет 0, то выходов нет, значит отмечаем их - это начало bfs
      for (uint32_t vertex : vector_exits_) {
        next_vertices[vertex] = 0;
      }
    }

    uint32_t max_distance = 0;   // максимальное расстояние, за исключением UINT32_MAX
    for (uint32_t distance : start_vertices) {
      if (distance != UINT32_MAX && distance > max_distance) {
        max_distance = distance;
      }
    }
    for (uint32_t i = 0; i < start_vertices.size(); i++) {  // теперь идем по ребрам от вершин, у которых макс расстояние
      if (start_vertices[i] == max_distance) {
        for (uint32_t vertex : adjacency_vectors_[i]) {
          if (start_vertices[vertex] == UINT32_MAX) {    // если до этого вершину не проходили, то значит заполняем её
            next_vertices[vertex] = max_distance + 1;
          }
        }
      }
    }
    return BreadthFirstSearch(next_vertices);
  }
   
 private:
  std::vector<std::vector<uint32_t>> adjacency_vectors_;
  uint32_t count_vertex_;
  uint32_t count_edges_;
  uint32_t count_exits_;
  std::vector<uint32_t> vector_exits_;
};

int main() {
  int n, k;
  std::cin >> n >> k;
  Graph graph(n, k);
  graph.ReadExits(std::cin);
  int m;
  std::cin >> m;
  graph.PutCountEdges(m);
  graph.ReadFromStream(std::cin);


  std::vector<uint32_t> start_vertices(n, UINT32_MAX);
  std::vector<uint32_t> result = graph.BreadthFirstSearch(start_vertices);
  for (uint32_t distance : result) {
    std::cout << distance << ' ';
  }
  std::cout << '\n';

  return 0;
}
