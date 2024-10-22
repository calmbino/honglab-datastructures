#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Matrix::Matrix(const int num_rows, const int num_cols) {
    this->num_rows_ = num_rows;
    this->num_cols_ = num_cols;
    const int capacity = this->num_rows_ * this->num_cols_;

    this->values_ = new float[capacity];

    for (int i = 0; i < capacity; i++) {
        this->values_[i] = 0.0f;
    }
}

Matrix::Matrix(const Matrix &b) {
    this->num_rows_ = b.num_rows_;
    this->num_cols_ = b.num_cols_;
    const int capacity = this->num_rows_ * this->num_cols_;

    this->values_ = new float[capacity];

    memcpy(this->values_, b.values_, capacity * sizeof(float));
}

Matrix::~Matrix() {
    delete[] this->values_;
}

void Matrix::SetValue(const int row, const int col, const float value) const {
    const int index = this->TransIndex(row, col);
    this->values_[index] = value;
}

float Matrix::GetValue(int row, int col) const {
    const int index = this->TransIndex(row, col);
    return this->values_[index];
}

Matrix Matrix::Add(const Matrix &b) const {
    assert(this->num_cols_ == b.num_cols_ && this->num_rows_ == b.num_rows_);

    const int capacity = this->num_rows_ * this->num_cols_;

    auto new_matrix = Matrix(this->num_rows_, this->num_cols_);

    for (int i = 0; i < this->num_rows_; i++) {
        for (int j = 0; j < this->num_cols_; j++) {
            const float sum = this->GetValue(i, j) + b.GetValue(i, j);
            new_matrix.SetValue(i, j, sum);
        }
    }

    for (int i = 0; i < capacity; i++) {
        new_matrix.values_[i] = this->values_[i] + b.values_[i];
    }

    return new_matrix;
}

Matrix Matrix::Transpose() const {
    // 전치행렬이기 때문에 row의 크기와 column의 크기가 바뀌어야 한다.
    auto new_matrix = Matrix(this->num_cols_, this->num_rows_);

    for (int i = 0; i < this->num_rows_; i++) {
        for (int j = 0; j < this->num_cols_; j++) {
            new_matrix.SetValue(j, i, this->GetValue(i, j));
        }
    }

    return new_matrix;
}

void Matrix::Print() const {
    for (int r = 0; r < this->num_rows_; r++) {
        for (int c = 0; c < this->num_cols_; c++)
            cout << GetValue(r, c) << " ";

        cout << endl;
    }
}

int Matrix::TransIndex(const int row, const int col) const {
    return col + num_cols_ * row;
}
