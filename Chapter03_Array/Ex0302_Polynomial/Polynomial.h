#pragma once

class Polynomial {
public:
    explicit Polynomial(int max_degree = 100);

    Polynomial(const Polynomial &poly);

    ~Polynomial();

    [[nodiscard]] int MaxDegree() const;

    void NewTerm(float coef, int exp);

    [[nodiscard]] Polynomial Add(const Polynomial &poly) const;

    [[nodiscard]] Polynomial Mult(const Polynomial &poly) const;

    [[nodiscard]] float Eval(float x) const;

    void Print() const;

private:
    int capacity_ = 0; // 항상 모든 항(term)들이 다 차 있는 것은 아니기 때문에 size 대신 capacity 사용
    float *coeffs_ = nullptr;
};
