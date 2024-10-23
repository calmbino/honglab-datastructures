#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols) {
    this->num_rows_ = num_rows;
    this->num_cols_ = num_cols;

    // num_rows개의 float 포인터 배열을 동적 할당
    this->arrays_ = new float *[this->num_rows_];

    // 각 행에 대해 num_cols 크기의 float 배열을 동적 할당 및 초기화
    for (int i = 0; i < this->num_rows_; i++) {
        this->arrays_[i] = new float[this->num_cols_]();
    }
}

Array2D::Array2D(const Array2D &b) {
    if (b.arrays_ == nullptr) {
        throw invalid_argument("The source array is null.");
    }

    this->num_rows_ = b.num_rows_;
    this->num_cols_ = b.num_cols_;

    // num_rows_개의 배열 할당
    this->arrays_ = new float *[this->num_rows_];

    for (int i = 0; i < this->num_rows_; i++) {
        // 각 행이 nullptr인지 확인
        if (b.arrays_[i] == nullptr) {
            throw std::invalid_argument("The source array row is null.");
        }

        // 각 행에 대해 num_cols_ 크기의 메모리 할당
        this->arrays_[i] = new float[this->num_cols_];

        // 행의 데이터를 복사
        memcpy(this->arrays_[i], b.arrays_[i], sizeof(float) * this->num_cols_);
    }
}

Array2D::~Array2D() {
    for (int i = 0; i < this->num_rows_; i++) {
        delete[] this->arrays_[i]; // 각 행을 해제
    }

    delete[] this->arrays_; // 배열 포인터 배열 해제
}

void Array2D::SetValue(const int row, const int col, const float value) const {
    this->arrays_[row][col] = value;
}

float Array2D::GetValue(const int row, const int col) const {
    return this->arrays_[row][col];
}

Array2D Array2D::Add(const Array2D &b) const {
    assert(this->num_rows_ == b.num_rows_ && this->num_cols_ == b.num_cols_);

    auto new_array = Array2D(this->num_rows_, this->num_cols_);

    for (int i = 0; i < this->num_rows_; i++) {
        for (int j = 0; j < this->num_cols_; j++) {
            new_array.SetValue(i, j, this->GetValue(i, j) + b.GetValue(i, j));
        }
    }

    return new_array;
}

Array2D Array2D::Transpose() const {
    auto new_array = Array2D(this->num_cols_, this->num_rows_);

    for (int i = 0; i < this->num_rows_; i++) {
        for (int j = 0; j < this->num_cols_; j++) {
            new_array.SetValue(j, i, this->GetValue(i, j));
        }
    }

    return new_array;
}


void Array2D::Print() const {
    for (int r = 0; r < num_rows_; r++) {
        for (int c = 0; c < num_cols_; c++)
            cout << GetValue(r, c) << " ";

        cout << endl;
    }
}
