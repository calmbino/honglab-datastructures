#pragma once
#include <string.h>

struct Term {
    float coef;
    int exp;
};

class SparsePolynomial {
public:
    // 아무것도 하지 않음 (동적할당 메모리 없이 시작)
    SparsePolynomial() = default;

    // 복사 생성자
    SparsePolynomial(const SparsePolynomial &poly) {
        this->capacity_ = poly.capacity_;
        this->num_terms_ = poly.num_terms_;
        terms_ = new Term[capacity_];

        memcpy(this->terms_, poly.terms_, sizeof(Term) * this->num_terms_);
    }

    ~SparsePolynomial() {
        if (terms_) delete[] terms_;
    }

    // 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함
    void NewTerm(float coef, int exp);

    [[nodiscard]] float Eval(float x) const;

    [[nodiscard]] SparsePolynomial Add(const SparsePolynomial &poly) const;

    void Print() const;

private:
    Term *terms_ = nullptr;
    int capacity_ = 0;
    int num_terms_ = 0;
};
