#pragma once

#include <cassert>
#include <iostream>

using namespace std;

template<typename T> // 템플릿 사용
class Stack {
public:
    explicit Stack(const int capacity = 1) {
        assert(capacity > 0);
        Resize(capacity);
    }

    ~Stack() {
        delete[] stack_;
    }

    void Resize(const int new_capacity) {
        T *new_stack = new T[new_capacity];
        memcpy(new_stack, stack_, sizeof(T) * Size());

        delete[] stack_;

        stack_ = new_stack;
        capacity_ = new_capacity;
    }

    [[nodiscard]] bool IsEmpty() const {
        return top_ < 0;
    }

    [[nodiscard]] int Size() const {
        return top_ + 1;
    }

    void Print() {
        for (int i = 0; i < Size(); i++) // Size() 사용
            cout << stack_[i] << " ";
        cout << endl;
    }

    // Returns TOP element of stack.
    T &Top() const {
        assert(!IsEmpty());

        return stack_[top_];
    }

    // Insert item into the TOP of the stack
    void Push(const T &item) {
        if (Size() == capacity_) {
            Resize(2 * capacity_);
        }

        // stack_[++top_] = item; // 아래 로직과 동일

        top_ += 1;
        stack_[top_] = item;
    }

    // Delete the TOP element of the stack
    void Pop() {
        assert(!IsEmpty());

        --top_;

        // 실제 물리적으로 메모리를 줄일 필요없다.
        // 논리적 제거를 하면 기존의 값이 그대로 남아 있지만 크게 문제되지 않는다.
        // 그런데 만약 T가 int, char와 같은 기본형이 아닌 복잡하고 커다란 타입이라면 메모리 관리가 필요할 수 있다.
        // stack_[top_--].~T(); // ex) 소멸자를 수동으로 호출
    }

protected: // 뒤에서 상속해서 사용
    T *stack_ = nullptr;
    int top_ = -1; // 0 아님
    int capacity_ = 0;
};
