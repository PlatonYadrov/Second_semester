#include <cmath>
#include <iostream>

class Bigint {
 public:
  static const int64_t kCell = 1e18;
  static const int kSize = 5;
  int64_t digits[kSize];
  Bigint() {
    for (int i = 0; i < kSize; ++i) {
      digits[i] = 0;
    }
  }

  explicit Bigint(int64_t var) {
    for (int i = 0; i < kSize; ++i) {
      digits[i] = 0;
    }
    int next = 0;
    while (var != 0) {
      digits[next] = var % kCell;
      var /= kCell;
      ++next;
    }
  }

  Bigint(const Bigint& other) {
    for (int i = 0; i < kSize; ++i) {
      digits[i] = other.digits[i];
    }
  }

  Bigint& operator=(const Bigint& other) {
    for (int i = 0; i < kSize; ++i) {
      digits[i] = other.digits[i];
    }
    return *this;
  }

  void operator+=(const Bigint& other) {
    for (int i = 0; i < kSize; ++i) {
      digits[i] += other.digits[i];
    }
    for (int i = 0; i < kSize - 1; ++i) {
      if (digits[i] >= kCell) {
        digits[i] -= kCell;
        ++digits[i + 1];
      }
    }
  }

  Bigint operator+(const Bigint& other) {
    Bigint n(*this);
    n += other;
    return n;
  }

  void operator-=(const Bigint& other) {
    for (int i = 0; i < kSize; ++i) {
      digits[i] -= other.digits[i];
    }
    for (int i = 0; i < kSize - 1; ++i) {
      if (digits[i] < 0) {
        digits[i] += kCell;
        --digits[i + 1];
      }
    }
  }

  Bigint operator-(const Bigint& other) {
    Bigint n(*this);
    n -= other;
    return n;
  }

  Bigint operator*(const Bigint& other) {
    Bigint result;
    for (int i = 0; i < kSize; ++i) {
      for (int j = 0; j < kSize - i; ++j) {
        result.digits[i + j] += digits[i] * other.digits[j];
      }
    }
    for (int i = 0; i < kSize - 1; ++i) {
      result.digits[i + 1] += result.digits[i] / kCell;
      result.digits[i] %= kCell;
    }
    return result;
  }

  void operator/=(int64_t var) {
    for (int i = kSize - 1; i >= 0; --i) {
      if (i > 0) {
        digits[i - 1] += (digits[i] % var) * kCell;
      }
      digits[i] /= var;
    }
  }
};

class Point {
 public:
  Bigint x;
  Bigint y;
};

int main() {
  int64_t amount;
  std::cin >> amount;
  auto* array = new Point[amount];
  for (int64_t i = 0; i < amount; ++i) {
    int64_t temp_x;
    int64_t temp_y;
    std::cin >> temp_x >> temp_y;
    Bigint temp__x(temp_x);
    Bigint temp__y(temp_y);
    array[i].x = temp__x;
    array[i].y = temp__y;
  }
  Bigint area(0);
  for (int i = 0; i < amount - 1; ++i) {
    area += array[i + 1].x * array[i].y - array[i].x * array[i + 1].y;
  }
  area += array[0].x * array[amount - 1].y - array[amount - 1].x * array[0].y;
  if (area.digits[0] % 2 == 0) {
    area /= static_cast<int64_t>(2);
    if (area.digits[0] < 0) {
      std::cout << -area.digits[0] << '.' << 0;
      delete[] array;
      return 0;
    }
    std::cout << area.digits[0] << '.' << 0;
  } else {
    area /= static_cast<int64_t>(2);
    if (area.digits[0] < 0) {
      std::cout << -area.digits[0] << '.' << 5;
      delete[] array;
      return 0;
    }
    std::cout << area.digits[0] << '.' << 5;
  }
  delete[] array;
  return 0;
}
