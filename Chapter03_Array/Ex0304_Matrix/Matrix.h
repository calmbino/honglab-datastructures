#pragma once

/**
 * - 2차원 공간의 배열 표기법 (row, column)
 * - 하지만 실제 메모리 관점에서 보면 1차원으로 관리
 * - 인덱스를 2차원 표기 방식에서 1차원 방식으로 전환이 가능
 * -- = column + num_columns * rows
 * -- ex) (0,0)은 0, (1, 2)는 6, (2 3)은 11
 * -- 즉, 3x4 행렬은 인덱스가 0부터 11까지인 1차원 배열로 표현이 가능
 */
class Matrix {
public:
    Matrix(int num_rows, int num_cols);

    Matrix(const Matrix &b);

    ~Matrix();

    void SetValue(int row, int col, float value) const;

    [[nodiscard]] float GetValue(int row, int col) const;

    [[nodiscard]] Matrix Add(const Matrix &b) const;

    [[nodiscard]] Matrix Transpose() const;

    void Print() const;

    [[nodiscard]] int TransIndex(int row, int col) const;

private:
    float *values_ = nullptr;
    int num_rows_ = 0;
    int num_cols_ = 0;
};
