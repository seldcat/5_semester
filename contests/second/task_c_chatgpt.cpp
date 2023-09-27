#include <iostream>
#include <vector>

class TGraph {
public:
  TGraph(int numVertices);
  void AddEdge(int u, int v);
  bool HasCycle() const;

private:
  int numVertices;
  std::vector<std::vector<int>> adjMatrix;
  std::vector<bool> visited;
  std::vector<bool> recStack;

  bool DepthFirstSearch(int v) const;
};

TGraph::TGraph(int numVertices) : numVertices(numVertices) {
  adjMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
  visited.resize(numVertices, false);
  recStack.resize(numVertices, false);
}

void TGraph::AddEdge(int u, int v) {
  adjMatrix[u][v] = 1;
}

bool TGraph::DepthFirstSearch(int v) const {
  if (!visited[v]) {
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < numVertices; ++i) {
      if (adjMatrix[v][i]) {
        if (!visited[i] && DepthFirstSearch(i)) {
          return true;
        } else if (recStack[i]) {
          return true;
        }
      }
    }
  }

  recStack[v] = false;
  return false;
}

bool TGraph::HasCycle() const {
  for (int i = 0; i < numVertices; ++i) {
    if (DepthFirstSearch(i)) {
      return true;
    }
  }
  return false;
}

int main() {
  int N;
  std::cin >> N;

  TGraph graph(N);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cin >> graph.adjMatrix[i][j];
    }
  }

  if (graph.HasCycle()) {
    std::cout << "1" << std::endl;
  } else {
    std::cout << "0" << std::endl;
  }

  return 0;
}
