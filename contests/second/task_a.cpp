
#include <iostream>
#include <vector>

class TGraph {
private:
    std::vector<std::vector<int>> adjacency_matrix_;
    uint32_t count_vertex_;
public:
    explicit TGraph(int n) {
        count_vertex_ = n;
        adjacency_matrix_.resize(count_vertex_);
        for(uint32_t i=0; i<count_vertex_; i++) {
            adjacency_matrix_[i].resize(count_vertex_);
            for(uint32_t j=0; j<count_vertex_; j++) {
                adjacency_matrix_[i][j] = 0;
            }
        }
    }

    void ReadFromStream(std::istream& stream) {
        for(uint32_t i=0; i<count_vertex_; i++) {
            for (uint32_t j=0; j<count_vertex_; j++) {
                stream >> adjacency_matrix_[i][j];
            }
        }
        return;
    }

    void output_data() const {
        for(int i=0; i<count_vertex_; i++) {
            for (int j=0; j<count_vertex_; j++) {
                std::cout << adjacency_matrix_[i][j];
            }
            std::cout << '\n';
        }
        return;
    }

    int GetConnectedComponent(const uint32_t vertex) const {
        std::vector<int> visited(count_vertex_);
        for(uint32_t i=0; i<count_vertex_; i++) {
            visited[i] = 0;
        }
        visited[vertex-1] = 1;

        for(uint32_t i=0; i<count_vertex_; i++) {
            if (adjacency_matrix_[vertex-1][i] == 1) {
                DepthFirstSearch(i, visited);
            } 
        }

        uint32_t result = 0;
        for(uint32_t i=0; i<count_vertex_; i++) {
            result += visited[i];
        }
        return result;
    }

private:
    void DepthFirstSearch(const uint32_t vertex, std::vector<int> &visited) const {
        visited[vertex] = 1;
        for(uint32_t i=0; i<count_vertex_; i++) {
            if (visited[i] != 1 and adjacency_matrix_[vertex][i] == 1) {
                DepthFirstSearch(i, visited);
            }
        }
    }
};

int main() {
    int N, S;
    std::cin >> N >> S;
    TGraph test(N);
    test.ReadFromStream(std::cin);
    // test.output_data();
    std::cout << test.GetConnectedComponent(S);
    return 0;
}
