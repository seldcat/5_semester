#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class TGraph {
public:
  TGraph(int numVertices);
  void AddEdge(int u, int v);
  void FindStronglyConnectedComponents();
  void TopologicalSort();
  void PrintStronglyConnectedComponents() const;

private:
  int numVertices;
  std::vector<std::vector<int>> adjList;
  std::vector<std::vector<int>> reverseAdjList;
  std::vector<int> visited;
  std::stack<int> dfsStack;
  std::vector<std::vector<int>> stronglyConnectedComponents;
  int currentComponent;

  void DFS(int u, bool reversed);
};

TGraph::TGraph(int numVertices) : numVertices(numVertices), currentComponent(0) {
  adjList.resize(numVertices + 1); // +1 for 1-based indexing
  reverseAdjList.resize(numVertices + 1); // +1 for 1-based indexing
  visited.resize(numVertices + 1, false); // +1 for 1-based indexing
}

void TGraph::AddEdge(int u, int v) {
  adjList[u].push_back(v);
  reverseAdjList[v].push_back(u);
}

void TGraph::DFS(int u, bool reversed) {
  visited[u] = true;
  std::vector<std::vector<int>>& graph = reversed ? reverseAdjList : adjList;

  for (int v : graph[u]) {
    if (!visited[v]) {
      DFS(v, reversed);
    }
  }

  if (!reversed) {
    dfsStack.push(u);
  } else {
    stronglyConnectedComponents[currentComponent].push_back(u);
  }
}

void TGraph::FindStronglyConnectedComponents() {
  for (int i = 1; i <= numVertices; ++i) {
    if (!visited[i]) {
      DFS(i, false);
    }
  }

  visited.assign(numVertices + 1, false); // Reset visited array

  while (!dfsStack.empty()) {
    int u = dfsStack.top();
    dfsStack.pop();

    if (!visited[u]) {
      stronglyConnectedComponents.push_back(std::vector<int>());
      DFS(u, true);
      currentComponent++;
    }
  }
}

void TGraph::TopologicalSort() {
  std::vector<int> order(numVertices);
  int index = 0;

  for (const std::vector<int>& component : stronglyConnectedComponents) {
    for (int u : component) {
      order[u - 1] = index++; // -1 to convert to 0-based indexing
    }
  }

  for (int i = 0; i < numVertices; ++i) {
    std::cout << order[i] << " ";
  }
  std::cout << "\n";
}

void TGraph::PrintStronglyConnectedComponents() const {
  std::cout << stronglyConnectedComponents.size() << "\n";
  for (const std::vector<int>& component : stronglyConnectedComponents) {
    for (int u : component) {
      std::cout << u << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int N, M;
  std::cin >> N >> M;

  TGraph graph(N);

  for (int i = 0; i < M; ++i) {
    int u, v;
    std::cin >> u >> v;
    graph.AddEdge(u, v);
  }

  graph.FindStronglyConnectedComponents();
  graph.TopologicalSort();

  return 0;
}
