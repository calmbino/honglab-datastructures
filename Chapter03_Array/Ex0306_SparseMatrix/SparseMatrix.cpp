#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(const int num_rows, const int num_cols, const int capacity) {
    this->num_rows_ = num_rows;
    this->num_cols_ = num_cols;
    this->capacity_ = capacity;

    this->terms_ = new MatrixTerm[this->capacity_];
}

SparseMatrix::SparseMatrix(const SparseMatrix &b) {
    if (b.terms_ == nullptr || b.num_terms_ <= 0) {
        throw invalid_argument("The source array is null.");
    }

    this->num_rows_ = b.num_rows_;
    this->num_cols_ = b.num_cols_;
    this->num_terms_ = b.num_terms_;
    this->capacity_ = b.capacity_;

    this->terms_ = new MatrixTerm[this->capacity_];

    memcpy(this->terms_, b.terms_, sizeof(MatrixTerm) * this->num_terms_);
}

SparseMatrix::~SparseMatrix() {
    delete[] this->terms_;
}


void SparseMatrix::SetValue(const int row, const int col, const float value) {
    if (value == 0.0f || row > this->num_rows_ || col > this->num_cols_) {
        throw invalid_argument("The input value is invalid.");
    }

    // 1) 용량(capacity) 확장
    if (this->capacity_ <= this->num_terms_) {
        const int new_capacity = this->capacity_ * 2;
        auto *new_matrix_term = new MatrixTerm[new_capacity];

        memcpy(new_matrix_term, this->terms_, sizeof(MatrixTerm) * this->num_terms_);

        delete[] this->terms_;

        this->terms_ = new_matrix_term;
        this->capacity_ = new_capacity;
    }

    // 2) 오름차순 정렬
    // row와 col을 이용하여 1차원 배열 기준의 인덱스로 변환
    const int new_term_key = col + this->num_cols_ * row;
    int insert_index = 0;
    for (; insert_index < this->num_terms_; insert_index++) {
        // row와 col을 이용하여 1차원 배열 기준의 인덱스로 변환
        const int origin_term_key = this->terms_[insert_index].col + this->num_cols_ * this->terms_[insert_index].row;

        if (origin_term_key == new_term_key) {
            // row와 col이 일치하는 원소가 존재하면 value만 업데이트 후 종료
            this->terms_[insert_index].value = value;

            return;
        }

        if (origin_term_key > new_term_key) {
            // 오름차순 정렬에 따라 새로운 항을 삽입해야하는 순간
            // 현재 인덱스부터는 한 칸씩 뒤로 이동해야한다
            break;
        }
    }


    // 3) 새로운 항을 삽입하기 위한 뒤로 밀기
    for (int i = this->num_terms_; i > insert_index; i--) {
        this->terms_[i] = this->terms_[i - 1];
    }

    // 4) 새로운 항 삽입
    this->terms_[insert_index].row = row;
    this->terms_[insert_index].col = col;
    this->terms_[insert_index].value = value;
    this->num_terms_ += 1;
}

float SparseMatrix::GetValue(const int row, const int col) const {
    const int search_term_key = col + this->num_cols_ * row;
    for (int i = 0; i < this->num_terms_; i++) {
        const int origin_term_key = this->terms_[i].col + this->num_cols_ * this->terms_[i].row;

        if (origin_term_key == search_term_key) {
            return this->terms_[i].value;
        }

        // 오름차순으로 정렬되어 있다면, 좀 더 빠르게 탐색을 끝낼 수 있다.
        if (origin_term_key > search_term_key) {
            break;
        }
    }

    return 0.0f;
}

SparseMatrix SparseMatrix::Transpose() const {
    auto new_sparse_matrix = SparseMatrix(this->num_cols_, this->num_rows_, this->capacity_);

    for (int i = 0; i < this->num_terms_; i++) {
        new_sparse_matrix.SetValue(this->terms_[i].col, this->terms_[i].row, this->terms_[i].value);
    }

    return new_sparse_matrix;
}

SparseMatrix SparseMatrix::Transpose02() const {
    auto new_sparse_matrix = SparseMatrix(this->num_cols_, this->num_rows_, this->capacity_);

    for (int r = 0; r < new_sparse_matrix.num_rows_; r++) {
        for (int i = 0; i < this->num_terms_; i++) {
            if (terms_[i].col == r) {
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].value = this->terms_[i].value;
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].col = this->terms_[i].row;
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].row = this->terms_[i].col;
                new_sparse_matrix.num_terms_ += 1;
            }
        }
    }

    return new_sparse_matrix;
}

void SparseMatrix::PrintTerms() const {
    for (int i = 0; i < num_terms_; i++)
        cout << "(" << terms_[i].row
                << ", " << terms_[i].col
                << ", " << terms_[i].value
                << ")" << endl;
}

void SparseMatrix::Print() const {
    for (int r = 0; r < num_rows_; r++) {
        for (int c = 0; c < num_cols_; c++)
            cout << GetValue(r, c) << " ";
        cout << endl;
    }
}
