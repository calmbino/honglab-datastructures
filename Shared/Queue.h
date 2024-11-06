#pragma once


#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class Queue // Circular Queue
{
public:
	explicit Queue(const int capacity = 2) {
		assert(capacity > 0);

		capacity_ = capacity;
		queue_ = new T[capacity_];
		front_ = 0;
		rear_ = 0;
	}

	~Queue() {
		delete[] queue_;
	}

	[[nodiscard]] bool IsEmpty() const {
		return front_ == rear_;
	}

	[[nodiscard]] bool IsFull() const {
		// 원형 큐에서 꽉 찼다의 기준
		// rear_가 앞으로 한 칸 전진했을 때, front_와 같은 위치라면 해당 큐는 꽉 찼다고 볼 수 있다.
		return (rear_ + 1) % capacity_ == front_;
	}

	T &Front() const {
		assert(!IsEmpty());

		return queue_[(front_ + 1) % capacity_]; // 주의 + 1
	}

	T &Rear() const {
		assert(!IsEmpty());

		return queue_[rear_];
	}

	[[nodiscard]] int Size() const {
		if (front_ <= rear_) {
			return rear_ - front_;
		} else {
			return capacity_ - (front_ - rear_);
		}
	}

	void Resize() // 2배씩 증가
	{
		assert(IsFull());

		const int new_capacity = capacity_ * 2;
		T *new_queue = new T[new_capacity];

		// memcpy에서 copy로 변환
		// T가 char, int와 같은 단순 타입이 아닌 string 등과 같은 객체 타입일 경우 문제가 발생
		// memcpy는 단순히 메모리를 바이트 단위로 복사할 뿐, 객체의 생성자나 복사 생성자를 호출하지 않는다.
		// 따라서 복사된 두 객체가 같은 메모리를 참조하게 되어, 한 객체가 소멸될 때 다른 객체의 내부 데이터가 해제되는 문제가 발생될 수 있다
		// copy는 객체의 특성을 고려한 안전한 복사 방식을 사용하기 때문에 memcpy 보다 안전하다.
		if (front_ < rear_) {
			// memcpy(new_queue, queue_, sizeof(T) * (Size() + 1));
			copy(queue_, queue_ + Size() + 1, new_queue);
		} else {
			// memcpy(&new_queue[1], &queue_[(front_ + 1) % capacity_], sizeof(T) * (capacity_ - 1 - front_));
			// memcpy(&new_queue[capacity_ - front_], queue_, sizeof(T) * (rear_ + 1));
			copy(&queue_[(front_ + 1) % capacity_], &queue_[capacity_], &new_queue[1]);
			copy(queue_, queue_ + (rear_ + 1), &new_queue[capacity_ - front_]);
		}

		rear_ = Size();
		front_ = 0;
		capacity_ = new_capacity;

		delete[] queue_;
		queue_ = new_queue;
	}

	void Enqueue(const T &item) // 맨 뒤에 추가, Push()
	{
		if (IsFull())
			Resize();

		int next_rear = (rear_ + 1) % capacity_;
		queue_[next_rear] = item;
		rear_ = next_rear;
	}

	void Dequeue() // 큐의 첫 요소 삭제, Pop()
	{
		assert(!IsEmpty());

		front_ = (front_ + 1) % capacity_;
	}

	void Print() {
		using namespace std;

		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
			cout << queue_[i] << " ";
		cout << endl;

		if (print_debug_)
			PrintDebug();
	}

	void PrintDebug() {
		using namespace std;

		cout << "Cap = " << capacity_ << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < capacity_; i++) {
			if (i == front_) cout << " F ";
			else if (i == rear_) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < capacity_; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (front_ < rear_) {
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < front_ + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = front_ + 1; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = rear_ + 1; i < capacity_; i++)
				cout << " * ";

			cout << endl << endl;
		} else if (front_ > rear_) {
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = rear_ + 1; i <= front_; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = front_ + 1; i < capacity_; i++)
				cout << setw(2) << queue_[i] << " ";

			cout << endl << endl;
		} else // 비었을 경우
		{
			for (int i = 0; i < capacity_; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag) {
		print_debug_ = flag;
	}

protected: // 뒤에서 상속해서 사용
	T *queue_; // array for queue elements
	int front_ = 0; // 시작 인덱스보다 하나 작은 값
	int rear_ = 0; // 마지막 인덱스 (첫 값은 1에 추가)
	int capacity_; // 빈 칸을 하나 둬야 하기 때문에 필요 메모리는 최대 저장량 + 1
	bool print_debug_ = false;
};
