#pragma once

#include <cassert>


template<typename T>
class SinglyLinkedList {
public:
	struct Node {
		T item = T();
		Node *next = nullptr;
	};

	SinglyLinkedList() = default;

	SinglyLinkedList(const SinglyLinkedList &list) {
		// 효율적인 방법
		Node *current = list.first_;
		while (current) {
			this->PushBack(current->item);
			current = current->next;
		}

		// 비효율적인 방법
		// Node *origin_node = list.first_;
		//
		// if (list.first_ == nullptr) {
		// 	first_ = nullptr;
		// 	return;
		// }
		//
		// Node *copied_node = new Node();
		//
		// first_ = copied_node;
		//
		// int index = 0;
		// while (origin_node != nullptr) {
		// 	copied_node->item = origin_node->item;
		//
		// 	if (index == list.Size() - 1) {
		// 		copied_node->next = nullptr;
		// 	} else {
		// 		copied_node->next = new Node();
		// 	}
		//
		// 	copied_node = copied_node->next;
		// 	origin_node = origin_node->next;
		// 	index++;
		// }
	}

	~SinglyLinkedList() {
		Clear();
	}

	void Clear() {
		// 방법 1
		while (first_ != nullptr) {
			PopFront();
		}

		// 방법 2
		// Node *node = first_;
		//
		// while (node != nullptr) {
		// 	const Node *current_node = node;
		// 	node = node->next;
		//
		// 	delete current_node;
		// }
		//
		// first_ = nullptr;
	}

	bool IsEmpty() {
		return first_ == nullptr;
	}

	[[nodiscard]] int Size() const {
		int size = 0;

		Node *node = first_;
		while (node != nullptr) {
			size += 1;
			node = node->next;
		}

		return size;
	}

	T Front() {
		assert(first_);

		return first_->item;
	}

	T Back() {
		assert(first_);

		Node *current = first_;
		while (current->next) {
			current = current->next;
		}

		return current->item;
	}

	Node *Find(T item) {
		Node *node = first_;

		while (node != nullptr) {
			if (node->item == item) {
				return node;
			}

			node = node->next;
		}

		return nullptr;
	}

	void InsertBack(Node *node, T item) {
		// 효율적인 방법
		Node *temp = new Node();
		temp->item = item;
		temp->next = node->next;
		node->next = temp;

		// 비효율적인 방법
		// Node *current_node = first_;
		//
		// while (current_node != nullptr) {
		// 	Node *temp = current_node->next;
		//
		// 	if (current_node == node) {
		// 		Node *new_node = new Node();
		// 		new_node->item = item;
		// 		new_node->next = current_node->next;
		// 		current_node->next = new_node;
		//
		// 		break;
		// 	}
		//
		// 	current_node = temp;
		// }
	}

	void Remove(Node *n) {
		assert(first_);

		// 효율적인 방법
		if (first_ == n) {
			first_ = first_->next;
			delete n;
			return;
		}

		Node *prev = first_;
		while (prev->next) {
			if (prev->next == n) {
				break;
			}

			prev = prev->next;
		}

		prev->next = n->next;
		delete n;

		// 비효율적인 방법
		// Node *node = first_;
		// Node *prev_node = nullptr;
		//
		// while (node != nullptr) {
		// 	if (node == n) {
		// 		if (n == first_) {
		// 			// 맨 앞을 삭제하는 경우
		// 			first_ = node->next;
		// 		} else {
		// 			prev_node->next = node->next;
		// 		}
		// 		delete node;
		// 		break;
		// 	}
		//
		// 	prev_node = node;
		// 	node = node->next;
		// }
	}

	void PushFront(T item) {
		Node *new_node = new Node();

		new_node->item = item;
		new_node->next = first_;

		first_ = new_node;
	}

	void PushBack(T item) {
		if (first_) {
			Node *current = first_;
			while (current->next) {
				// 마지막 Node 찾기
				current = current->next;
			}

			Node *new_node = new Node();
			new_node->item = item;
			new_node->next = nullptr;

			current->next = new_node;
		} else {
			PushFront(item);
		}
	}

	void PopFront() {
		if (IsEmpty()) {
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		const Node *node = first_;
		first_ = first_->next;

		delete node;
	}

	void PopBack() {
		if (IsEmpty()) {
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		//방법 1
		if (first_->next == nullptr) {
			delete first_;
			first_ = nullptr;
			return;
		}

		assert(first_);

		Node *second_last = first_;

		while (second_last->next->next) {
			second_last = second_last->next;
		}

		const Node *temp = second_last->next;
		second_last->next = second_last->next->next;

		delete temp;

		// 방법 2
		// assert(first_);
		//
		// Node *node = first_;
		//
		// int index = 0;
		// while (node != nullptr) {
		// 	if (index == Size() - 2) {
		// 		const Node *temp = node->next;
		// 		node->next = nullptr;
		//
		// 		delete temp;
		// 		break;
		// 	}
		//
		// 	node = node->next;
		// 	index++;
		// }
	}

	void Reverse() {
		// 효율적인 방법
		Node *current_node = first_;
		Node *prev_node = nullptr;

		while (current_node) {
			Node *temp = prev_node;
			prev_node = current_node;
			current_node = current_node->next;
			prev_node->next = temp;
		}

		first_ = prev_node;

		// 비효율적인 방법
		// Node *current_node = first_;
		// Node *prev_node = nullptr;
		// Node *next_node = nullptr;
		//
		// int index = 0;
		// int lenth = Size();
		// while (current_node != nullptr) {
		// 	next_node = current_node->next;
		//
		// 	if (index == lenth) {
		// 		first_ = current_node;
		// 	}
		//
		// 	current_node->next = prev_node;
		//
		// 	prev_node = current_node;
		// 	current_node = next_node;
		//
		// 	index++;
		// }
	}

	void SetPrintDebug(bool flag) {
		print_debug_ = flag;
	}

	void Print() {
		using namespace std;

		Node *current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else {
			cout << "Size = " << Size() << " ";

			while (current) {
				if (print_debug_) {
					// cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
							<< current->item << ", "
							<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				} else {
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node *first_ = nullptr;

	bool print_debug_ = false;
};
