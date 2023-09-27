// Google style code
#include <iostream>
#include <vector>
#include <numeric>
#include <list>

class Graph {
 public:
  explicit Graph(uint32_t n, uint32_t k) : adjacency_vectors_(n, std::vector<uint32_t>()), count_vertex_(n), count_exits_(k), vector_exits_() {}
   
  void PutCountEdges(uint32_t n) {
    count_edges_ = n;
  }

  void ReadExits(std::istream& stream) {
    uint32_t vertex;
    for (int i = 0; i < count_exits_; i++) {
      stream >> vertex;
      vector_exits_.push_back(vertex - 1);
    }
  }

  void ReadFromStream(std::istream& stream) {
    int left_vertex, right_vertex;
    for (int i = 0; i < count_edges_; i++) {
      stream >> left_vertex >> right_vertex;
      adjacency_vectors_[left_vertex - 1].push_back(right_vertex - 1);
      adjacency_vectors_[right_vertex - 1].push_back(left_vertex - 1);
    }
  }

  std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& start_vertices) const {
    for (int i = 0; i < start_vertices.size(); i++) {
      std::cout << start_vertices[i] << ' ';
    }
    std::cout << '\n';

    bool is_there_only_visited_vertex = true;
    uint32_t maximum = -1;     // максимальное значение в векторе - это максимальное расстояние от выходов
    for (int i = 0; i < start_vertices.size(); i++) {
      if (start_vertices[i] == -1) {
        is_there_only_visited_vertex = false;
      }
      if (maximum < start_vertices[i]) {
        maximum = start_vertices[i];
      }
    }

    if (is_there_only_visited_vertex) {    // когда непосещенных вершин нет, мы закончили
      return start_vertices;
    }

    std::vector<uint32_t> next_vertices(count_vertex_, -1);
    if (maximum == -1) {       // если максимум равен -1, то обозначаем где у нас выходы - помечаем их 0
      for (int i = 0; i < vector_exits_.size(); i++) {
        next_vertices[vector_exits_[i]] = 0;
      }
      return BreadthFirstSearch(next_vertices);
    }

    for (int i = 0; i < start_vertices.size(); i++) {  // иначе идем от максимальных значений по ребрам
      if (start_vertices[i] == maximum) {
        next_vertices[i] = maximum;
        for (int j = 0; j < adjacency_vectors_[i].size(); j++) {
          if (start_vertices[adjacency_vectors_[i][j]] == -1) {    // если до этого вершину не проходили, то значит заполняем её
            next_vertices[adjacency_vectors_[i][j]] = maximum + 1;
          }
        }
      } else {
        if (start_vertices[i] != -1) {
          next_vertices[i] = start_vertices[i];
        }
      }
    }
    return BreadthFirstSearch(next_vertices);
  }

  void OutputData() {
    std::cout << "Exits: ";
    for (int i = 0; i < count_exits_; i++)
      std::cout << vector_exits_[i] << " ";
    std::cout << '\n';
    std::cout << "count_vertex_ = " << count_vertex_ << '\n';
    std::cout << "count_edges_ = " << count_edges_ << '\n';
    std::cout << "adjacency_vectors_: \n";
    for (int i = 0; i < count_vertex_; i++) {
      for (int j = 0; j < adjacency_vectors_[i].size(); j++) {
        std::cout << adjacency_vectors_[i][j] + 1 << ' ';
      }
      std::cout << '\n';
    }
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


  std::vector<uint32_t> start_vertices(n, -1);
  std::vector<uint32_t> result = graph.BreadthFirstSearch(start_vertices);
  for (int i = 0; i < result.size(); i++) {
    std::cout << result[i] << ' ';
  }

  return 0;
}
