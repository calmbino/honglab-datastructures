#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T> {
    typedef Queue<T> Base;

public:
    explicit Deque(int capacity)
        : Queue<T>(capacity) {
    }

    T &Front() {
        return Base::Front();
    }

    T &Back() {
        return Base::Rear();
    }

    void PushFront(const T &item) {
        if (Base::IsFull())
            Base::Resize();

        Base::queue_[Base::front_] = item;
        Base::front_ = Base::front_ == 0 ? Base::capacity_ - 1 : (Base::front_ - 1) % Base::capacity_;
        // Base::front_ = (Base::front_ - 1 + Base::capacity_) % Base::capacity_; // 위와 동일
    }

    void PushBack(const T &item) {
        Base::Enqueue(item);
    }

    void PopFront() {
        Base::Dequeue();
    }

    void PopBack() {
        assert(!Base::IsEmpty());

        Base::rear_ = Base::rear_ == 0 ? Base::capacity_ - 1 : (Base::rear_ - 1) % Base::capacity_;
        // Base::rear_ = (Base::rear_ -1 + Base::capacity_) % Base::capacity_; // 위와 동일
    }

private:
    // Queue와 동일

    // 참고) 부모 클래스의 멤버 변수를 레퍼런스(&)를 통해 받으면 동일하게 사용 가능하다.
    int &front_ = Base::front_;
    int &rear_ = Base::rear_;
};
