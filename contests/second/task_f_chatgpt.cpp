#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>

class TGraph {
public:
  TGraph(int numRoutes, int numStops);
  void AddRoute(const std::vector<int>& route);
  bool FindEulerianCycle();
  std::vector<int> GetEulerianCycle() const;

private:
  int numRoutes;
  int numStops;
  std::unordered_map<int, std::vector<int>> graph;
  std::vector<int> eulerianCycle;
  std::stack<int> dfsStack;

  void DFS(int startNode);
};

TGraph::TGraph(int numRoutes, int numStops) : numRoutes(numRoutes), numStops(numStops) {}

void TGraph::AddRoute(const std::vector<int>& route) {
  for (int i = 1; i < route.size(); ++i) {
    int u = route[i - 1];
    int v = route[i];
    graph[u].push_back(v);
  }
}

void TGraph::DFS(int startNode) {
  dfsStack.push(startNode);

  while (!dfsStack.empty()) {
    int u = dfsStack.top();

    if (graph[u].empty()) {
      eulerianCycle.push_back(u);
      dfsStack.pop();
    } else {
      int v = graph[u].back();
      graph[u].pop_back();
      dfsStack.push(v);
    }
  }
}

bool TGraph::FindEulerianCycle() {
  int oddDegreeNodes = 0;
  int startNode = -1;

  for (const auto& kvp : graph) {
    int node = kvp.first;
    int outDegree = kvp.second.size();
    int inDegree = 0;

    for (const auto& kvp2 : graph) {
      const std::vector<int>& neighbors = kvp2.second;
      inDegree += std::count(neighbors.begin(), neighbors.end(), node);
    }

    if (inDegree != outDegree) {
      return false;
    }

    if (outDegree % 2 == 1) {
      oddDegreeNodes++;
      startNode = node;
    }
  }

  if (oddDegreeNodes == 0 || oddDegreeNodes == 2) {
    DFS(startNode != -1 ? startNode : graph.begin()->first);
    return true;
  }

  return false;
}

std::vector<int> TGraph::GetEulerianCycle() const {
  return eulerianCycle;
}

int main() {
  int N, M;
  std::cin >> N >> M;

  TGraph graph(N, M);

  for (int i = 0; i < N; ++i) {
    int k;
    std::cin >> k;
    std::vector<int> route(k + 1);
    for (int j = 0; j <= k; ++j) {
      std::cin >> route[j];
    }
    graph.AddRoute(route);
  }

  if (graph.FindEulerianCycle()) {
    std::vector<int> eulerianCycle = graph.GetEulerianCycle();
    if (eulerianCycle.size() == M + 1) {
      std::cout << "0\n";
    } else {
      std::cout << eulerianCycle.size() - 1 << "\n";
      for (int i = 0; i < eulerianCycle.size() - 1; ++i) {
        std::cout << eulerianCycle[i] << " ";
      }
      std::cout << "\n";
    }
  } else {
    std::cout << "0\n";
  }

  return 0;
}
