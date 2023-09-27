#include <iostream>
#include <vector>
#include <queue>

class TGraph {
public:
  TGraph(int numSoldiers);
  void AddRelation(int a, int b);
  bool CanSatisfyPoliceman() const;
  std::vector<int> GetValidOrder() const;

private:
  int numSoldiers;
  std::vector<std::vector<int>> adjList;
  std::vector<int> inDegree;

  bool TopologicalSort(std::vector<int>& order) const;
};

TGraph::TGraph(int numSoldiers) : numSoldiers(numSoldiers) {
  adjList.resize(numSoldiers + 1); // +1 for 1-based indexing
  inDegree.resize(numSoldiers + 1, 0); // +1 for 1-based indexing
}

void TGraph::AddRelation(int a, int b) {
  adjList[a].push_back(b);
  inDegree[b]++;
}

bool TGraph::TopologicalSort(std::vector<int>& order) const {
  std::queue<int> q;
  for (int i = 1; i <= numSoldiers; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);

    for (int v : adjList[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }

  return order.size() == numSoldiers;
}

bool TGraph::CanSatisfyPoliceman() const {
  std::vector<int> order;
  if (!TopologicalSort(order)) {
    return false;
  }

  std::vector<int> pos(numSoldiers + 1); // +1 for 1-based indexing
  for (int i = 0; i < numSoldiers; ++i) {
    pos[order[i]] = i;
  }

  for (int i = 1; i <= numSoldiers; ++i) {
    for (int v : adjList[i]) {
      if (pos[i] > pos[v]) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  int N, M;
  std::cin >> N >> M;

  TGraph graph(N);

  for (int i = 0; i < M; ++i) {
    int A, B;
    std::cin >> A >> B;
    graph.AddRelation(A, B);
  }

  if (graph.CanSatisfyPoliceman()) {
    std::cout << "Yes\n";
    std::vector<int> validOrder = graph.GetValidOrder();
    for (int i = 0; i < N; ++i) {
      std::cout << validOrder[i] << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "No\n";
  }

  return 0;
}
