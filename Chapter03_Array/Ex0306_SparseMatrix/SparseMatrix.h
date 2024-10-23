#pragma once

struct MatrixTerm {
    int row;
    int col;
    float value;
};

class SparseMatrix {
public:
    SparseMatrix(int num_rows, int num_cols, int capacity);

    SparseMatrix(const SparseMatrix &b);

    ~SparseMatrix();

    [[nodiscard]] int TransIndex(int row, int col) const;

    void SetValue(int row, int col, float value); // NewTerm()

    float GetValue(int row, int col) const;

    SparseMatrix Transpose() const;

    SparseMatrix Transpose02() const;

    void PrintTerms() const;

    void Print() const;

private:
    MatrixTerm *terms_ = nullptr; // Non-zero terms
    int num_rows_ = 0; // 최대 rows 갯수
    int num_cols_ = 0; // 최대 columns 갯수
    int num_terms_ = 0;
    int capacity_ = 0;
};
