#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

void SparsePolynomial::NewTerm(float coef, int exp) {
    if (coef == 0.0f) return;

    // 먼저 같은 exp 값이 존재하는지 확인
    for (int i = 0; i < num_terms_; i++) {
        if (terms_[i].exp == exp) {
            // 같은 exp가 존재하면 계수를 더함
            terms_[i].coef += coef;
            if (terms_[i].coef == 0.0f) {
                // 만약 계수가 0이 되면 항을 삭제
                for (int j = i; j < num_terms_ - 1; j++) {
                    terms_[j] = terms_[j + 1];
                }
                --num_terms_;
            }
            return; // 이미 처리했으므로 함수 종료
        }
    }

    // capacity가 부족하면 확장
    // 일반적으로 메모리 재할당에 걸리는 시간은 메모리의 크기와 무관하다고 한다.
    if (num_terms_ >= capacity_) {
        capacity_ = capacity_ > 0 ? 2 * capacity_ : 1; // 첫 번째 추가 이후에는 배열 공간을 2배씩 증가
        Term *new_terms = new Term[capacity_];

        // 기존 내용들을 복사
        memcpy(new_terms, terms_, sizeof(Term) * num_terms_);

        // 메모리 교체
        delete[] terms_;
        terms_ = new_terms;
    }

    // 오름차순으로 정렬하기 위한 삽입 위치 찾기
    int insert_pos = num_terms_;
    for (int i = 0; i < num_terms_; i++) {
        if (terms_[i].exp > exp) {
            insert_pos = i;
            break;
        }
    }

    // 새로운 항을 삽입하기 위해 뒤로 밀기
    for (int i = num_terms_; i > insert_pos; i--) {
        terms_[i] = terms_[i - 1];
    }

    terms_[insert_pos].coef = coef;
    terms_[insert_pos].exp = exp;

    num_terms_++;
}

float SparsePolynomial::Eval(const float x) const {
    float sum = 0.0f;
    for (int i = 0; i < num_terms_; i++) {
        sum += terms_[i].coef * powf(x, static_cast<float>(this->terms_[i].exp));
    }

    return sum;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial &poly) const {
    SparsePolynomial new_polynomial;

    int i = 0;
    int j = 0;

    while (true) {
        if (i >= this->num_terms_ || j >= poly.num_terms_) break;

        if (this->terms_[i].exp == poly.terms_[j].exp) {
            const float sum = this->terms_[i].coef + poly.terms_[j].coef;

            // 계수가 0이 아닌 경우에만 새로운 항 추가
            if (sum != 0.0f) {
                new_polynomial.NewTerm(sum, this->terms_[i].exp);
            }

            i++;
            j++;
        } else {
            if (this->terms_[i].exp > poly.terms_[j].exp) {
                new_polynomial.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
                j++;
            } else {
                new_polynomial.NewTerm(this->terms_[i].coef, this->terms_[i].exp);
                i++;
            }
        }
    }

    for (; i < this->num_terms_; i++) {
        new_polynomial.NewTerm(this->terms_[i].coef, this->terms_[i].exp);
    }
    for (; j < poly.num_terms_; j++) {
        new_polynomial.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
    }

    return new_polynomial;
}

void SparsePolynomial::Print() const {
    bool is_first = true; // 더하기 출력시 확인용

    for (int i = 0; i < num_terms_; i++) {
        // 0이 아닌 항들만 골라서 출력할 필요가 없음

        if (!is_first)
            cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

        cout << terms_[i].coef;

        if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

        is_first = false;
    }

    cout << endl;
}
