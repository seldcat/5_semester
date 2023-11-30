#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Square {
  public:
  Square(): square_(16, 0) {}

  void ReadFromStream(std::istream& stream) {
    for (size_t i = 0; i < 16; i++) {
      stream >> square_[i];
    }
  }

  void WriteToStream(std::ostream& stream) const {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        stream << std::setw(6) << square_[i * 4 + j];
      }
      stream << std::endl;
    }
  }

  bool IsMagicSquare() {
    do {
      if (IsMagicCurrentSquare()) {
        return true;
      }
    } while (std::next_permutation(square_.begin(), square_.end()));
    return false;
  }

  private:
  bool IsMagicCurrentSquare() {
    uint32_t first_row = square_[0] + square_[1] + square_[2] + square_[3];
    for (int i = 1; i < 4; i++) {
      uint32_t row_sum = 0;
      for (int j = 0; j < 4; j++) {
        row_sum += square_[i * 4 + j];
      }
      if (row_sum != first_row) {
        return false;
      }
    }

    uint32_t first_column = square_[0] + square_[4] + square_[8] + square_[12];
    for (int i = 0; i < 4; i++) {
      uint32_t column_sum = 0;
      for (int j = 1; j < 4; j++) {
        column_sum += square_[4 * j + i];
      }
      if (column_sum != first_column) {
        return false;
      }
    }

    return true;
  }

  std::vector<uint32_t> square_;
};

int main() {
  Square square;

  square.ReadFromStream(std::cin);

  if (square.IsMagicSquare()) {
    square.WriteToStream(std::cout);
  } else {
    std::cout << "NO SOLUTION";
  }

  return 0;
}
