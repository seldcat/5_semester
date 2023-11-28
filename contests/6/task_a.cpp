#include <iostream>
#include <vector>
#include <algorithm>

class Backpack {
 public:
  Backpack(const uint32_t n, const uint32_t w): item_count_(n), max_weight_(w), weights_(n, 0), prices_(n, 0), matrix_of_prices_(n + 1, std::vector<uint32_t>(w + 1, 0)) {}

  void ReadFromStream(std::istream& stream) {
    for (uint32_t i = 0; i < item_count_; i++) {
      stream >> weights_[i];
    }
    for (uint32_t i = 0; i < item_count_; i++) {
      stream >> prices_[i];
    }
    BuildMatrixOfPrices();
  }

  uint32_t MaxPrice() const {
    uint32_t answer = 0;
    for (uint32_t i = 0; i <= item_count_; i++) {
      for (uint32_t j = 0; j <= max_weight_; j ++) {
        if (matrix_of_prices_[i][j] > answer) {
          answer = matrix_of_prices_[i][j];
        }
      }
    }
    return answer;
  }

 private:
  void BuildMatrixOfPrices() {
    for (uint32_t k = 1; k <= item_count_; k++) {
      for (uint32_t w = 0; w <= max_weight_; w++) {
        if (w >= weights_[k - 1]) {
          matrix_of_prices_[k][w] = std::max(matrix_of_prices_[k - 1][w], matrix_of_prices_[k - 1][w - weights_[k - 1]] + prices_[k - 1]);
        } else {
          matrix_of_prices_[k][w] = matrix_of_prices_[k - 1][w];
        }
      }
    }
  }

  uint32_t item_count_, max_weight_;
  std::vector<uint32_t> weights_, prices_;
  std::vector<std::vector<uint32_t>> matrix_of_prices_;
};

int main() {
  uint32_t N, M;
  std::cin >> N >> M;

  Backpack bag(N, M);
  bag.ReadFromStream(std::cin);

  std::cout << bag.MaxPrice();

  return 0;
}
