#pragma once

/**
  * - 이번에는 2차원 배열을 2중 포인터를 이용하여 구현
  */
class Array2D {
public:
    Array2D(int num_rows, int num_cols);

    Array2D(const Array2D &b);

    ~Array2D();

    void SetValue(int row, int col, float value) const;

    [[nodiscard]] float GetValue(int row, int col) const;

    [[nodiscard]] Array2D Add(const Array2D &b) const;

    [[nodiscard]] Array2D Transpose() const;

    void Print() const;

private:
    float **arrays_ = nullptr; // 2중 포인터
    int num_rows_ = 0;
    int num_cols_ = 0;
};
