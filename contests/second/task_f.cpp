// Google style code
#include <vector>
#include <iostream>
#include <numeric>

class Graph {
 public:
  explicit Graph(uint32_t n, uint32_t m) : adjacency_matrix_(m, std::vector<int>(m, 0)), vertex_count_(m), bus_count_(n), deg_(m, 0) {}
  ~Graph() {}
  
  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < bus_count_; i++) {
      uint32_t stations_count;
      stream >> stations_count;
      uint32_t previous_vertex, current_vertex;
      stream >> previous_vertex;
      for (uint32_t j = 0; j < stations_count; j++) {
        stream >> current_vertex;
        adjacency_matrix_[previous_vertex - 1][current_vertex - 1] = 1;
        deg_[previous_vertex - 1]++;
        previous_vertex = current_vertex;
      }
    }
  }
  
  std::vector<uint32_t> FindEulerPath() const {
    // сначала проверяем на эйлеровость/полуэйлеровость граф
    if (!CheckForEulerPath()) {
      return {0};
    }
    // подготавливаем копию матрицы смежности и вектор, в котором будет находиться путь по итогу
    std::vector<std::vector<int>> matrix_copy(vertex_count_, std::vector<int>(vertex_count_));
    for (uint32_t i = 0; i < vertex_count_; i++) {
      for (uint32_t j =0; j < vertex_count_; j++) {
        matrix_copy[i][j] = adjacency_matrix_[i][j];
      }
    }
    std::vector<uint32_t> result_way;
    // теперь надо построить сам путь
    // если граф полуэйлеровый, надо начинать построение с нечетной вершины, поэтому сначала проверяется, есть ли она
    // если мы нашли нечетную вершину, то запускаем построение пути и выводим его
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (deg_[i] % 2 == 1) {
        GetEulerPath(i, result_way, matrix_copy);
        return result_way;
      }
    }
    // если не нашли нечетную вершину, то вышли из for цикла и начинаем построение из первой вершины c ненулевой степенью
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (deg_[i] != 0) {
        GetEulerPath(i, result_way, matrix_copy);
        return result_way;
      }
    }
  }
  
 private:
  bool CheckForEulerPath() const {
    uint32_t odd_vertex_count = 0;
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (deg_[i] % 2 == 1) {
        odd_vertex_count++;
      }
    }
    if (odd_vertex_count > 2) {
      return false;
    }
    return true;
  }
  
  void GetEulerPath(int vertex, std::vector<uint32_t>& result_way, std::vector<std::vector<int>> adjacency_matrix) const {
    for (uint32_t i = 0; i < vertex_count_; i++) {
      if (adjacency_matrix[vertex][i]) {
        adjacency_matrix[vertex][i] = 0;
        GetEulerPath(i, result_way, adjacency_matrix);
      }
    }
    result_way.push_back(vertex + 1);
  }
  
  std::vector<std::vector<int>> adjacency_matrix_;
  uint32_t vertex_count_;
  uint32_t bus_count_;
  std::vector<uint32_t> deg_;
};

int main() {
  uint32_t n, m;
  std::cin >> n >> m;
  Graph graph(n, m);
  graph.ReadFromStream(std::cin);
  std::vector<uint32_t> euler_path = graph.FindEulerPath();
  if (euler_path[0] == 0) {
    std::cout << 0 << '\n';
  } else {
    std::cout << euler_path.size() << ' ';
    for (uint32_t vertex : euler_path) {
      std::cout << vertex << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
