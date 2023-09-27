#include <iostream>
#include <vector>
#include <queue>

class TGraph {
public:
  TGraph(uint32_t numVertices);
  void AddEdge(uint32_t u, uint32_t v);
  std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const;

private:
  uint32_t numVertices;
  std::vector<std::vector<uint32_t>> adjList;
};

TGraph::TGraph(uint32_t numVertices) : numVertices(numVertices), adjList(numVertices) {}

void TGraph::AddEdge(uint32_t u, uint32_t v) {
  adjList[u].push_back(v);
  adjList[v].push_back(u);
}

std::vector<uint32_t> TGraph::BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const {
  std::vector<uint32_t> distances(numVertices, UINT32_MAX);
  std::queue<uint32_t> queue;

  for (uint32_t startVertex : startVertices) {
    distances[startVertex] = 0;
    queue.push(startVertex);
  }

  while (!queue.empty()) {
    uint32_t u = queue.front();
    queue.pop();

    for (uint32_t v : adjList[u]) {
      if (distances[v] == UINT32_MAX) {
        distances[v] = distances[u] + 1;
        queue.push(v);
      }
    }
  }

  return distances;
}

int main() {
  uint32_t N, K, M;
  std::cin >> N >> K;

  std::vector<uint32_t> exits(K);
  for (uint32_t i = 0; i < K; ++i) {
    std::cin >> exits[i];
    exits[i]--; // Convert to 0-based indexing
  }

  TGraph graph(N);

  std::cin >> M;
  for (uint32_t i = 0; i < M; ++i) {
    uint32_t u, v;
    std::cin >> u >> v;
    u--; v--; // Convert to 0-based indexing
    graph.AddEdge(u, v);
  }

  std::vector<uint32_t> distances = graph.BreadthFirstSearch(exits);

  for (uint32_t i = 0; i < N; ++i) {
    std::cout << distances[i] << " ";
  }

  return 0;
}
