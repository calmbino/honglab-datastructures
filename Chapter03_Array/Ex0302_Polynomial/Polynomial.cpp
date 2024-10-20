#include "Polynomial.h"

#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

Polynomial::Polynomial(const int max_degree) {
    // 편의상 기본값(100) 사용
    assert(max_degree >= 0);

    this->capacity_ = max_degree + 1; // 상수항 포함
    this->coeffs_ = new float[capacity_]; // 동적 메모리 할당

    // 모든 항을 0으로 초기화
    for (int i = 0; i < capacity_; i++) {
        coeffs_[i] = 0.0f;
    }
}

Polynomial::Polynomial(const Polynomial &poly) {
    this->capacity_ = poly.capacity_;
    this->coeffs_ = new float[this->capacity_];

    memcpy(this->coeffs_, poly.coeffs_, sizeof(float) * this->capacity_);
}

Polynomial::~Polynomial() {
    delete[] this->coeffs_;
}

int Polynomial::MaxDegree() const {
    int max_degree = -1;

    for (int i = 0; i < this->capacity_; i++) {
        if (this->coeffs_[i] != 0) {
            max_degree = i;
        }
    }

    return max_degree;
}

void Polynomial::NewTerm(const float coef, const int exp) {
    // exp가 현재 다항식의 최대 차수보다 큰 경우, 크기를 재조정
    // 차수와 수용할 수 있는 공간을 비교하는 것이 부적절하지만, 이는 위 생성자에서 기본 차수를 100으로 설정했기 때문에 나타나는 한계점
    if (this->capacity_ <= exp) {
        const int new_capacity = exp + 1;
        const auto new_coeffs = new float[new_capacity];

        for (int i = 0; i < new_capacity; i++) {
            new_coeffs[i] = 0.0f;
        }
        // 기존 배열의 값 복사
        memcpy(new_coeffs, this->coeffs_, sizeof(float) * this->capacity_);
        new_coeffs[exp] = coef;

        delete[] this->coeffs_;

        this->coeffs_ = new_coeffs;
        this->capacity_ = new_capacity;
    } else {
        this->coeffs_[exp] = coef;
    }
}

Polynomial Polynomial::Add(const Polynomial &poly) const {
    // 두 다항식 중 더 큰 차수로 결과 다항식 크기 설정
    const int new_max_degree = max(this->MaxDegree(), poly.MaxDegree());
    Polynomial new_poly(new_max_degree); // 새로운 다항식 생성 (적절한 크기 할당)

    // 두 다항식을 더함 (계수가 존재하는 경우에만 더함)
    for (int i = 0; i <= new_max_degree; i++) {
        const float this_coeff = (i <= this->MaxDegree()) ? this->coeffs_[i] : 0.0f;
        const float poly_coeff = (i <= poly.MaxDegree()) ? poly.coeffs_[i] : 0.0f;

        new_poly.coeffs_[i] = this_coeff + poly_coeff;
    }

    // Polynomial new_poly;
    // if (this->MaxDegree() >= poly.MaxDegree()) {
    //     for (int i = 0; i < poly.MaxDegree() + 1; i++) {
    //         new_poly.coeffs_[i] = this->coeffs_[i] + poly.coeffs_[i];
    //     }
    //     for (int i = poly.MaxDegree() + 1; i < this->MaxDegree() + 1; i++) {
    //         new_poly.coeffs_[i] = this->coeffs_[i];
    //     }
    // } else {
    //     for (int i = 0; i < this->MaxDegree() + 1; i++) {
    //         new_poly.coeffs_[i] = this->coeffs_[i] + poly.coeffs_[i];
    //     }
    //     for (int i = this->MaxDegree() + 1; i < poly.MaxDegree() + 1; i++) {
    //         new_poly.coeffs_[i] = poly.coeffs_[i];
    //     }
    // }

    return new_poly;
}

Polynomial Polynomial::Mult(const Polynomial &poly) const {
    const int new_max_degree = this->MaxDegree() + poly.MaxDegree();
    Polynomial new_poly(new_max_degree);


    for (int i = 0; i < poly.MaxDegree() + 1; i++) {
        const float target = poly.coeffs_[i];
        for (int j = 0; j < this->MaxDegree() + 1; j++) {
            new_poly.coeffs_[i + j] += this->coeffs_[j] * target;
        }
    }

    return new_poly;
}

float Polynomial::Eval(float x) const {
    float sum = 0.0f;

    for (int i = 0; i < this->MaxDegree() + 1; i++) {
        sum += this->coeffs_[i] * powf(x, static_cast<float>(i));
    }

    return sum;
}

void Polynomial::Print() const {
    bool is_first = true; // 더하기 출력시 확인용

    for (int i = 0; i < capacity_; i++) {
        if (coeffs_[i] != 0.0f) // 주의: 0이 아닌 항들만 출력
        {
            if (!is_first)
                cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

            cout << coeffs_[i];

            if (i != 0) cout << "*" << "x^" << i;

            is_first = false;
        }
    }

    cout << endl;
}
