#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList {
public:
    struct Node {
        T item = T();

        Node *left = nullptr;
        Node *right = nullptr;

        // 참고: prev/next가 아니라 left/
    };

    DoublyLinkedList() {
    }

    // 복사 생성자
    DoublyLinkedList(const DoublyLinkedList &list) {
        Node *current = list.first_;

        while (current) {
            this->PushBack(current->item);
            current = current->right;
        }
    }

    ~DoublyLinkedList() {
        Clear();
    }

    void Clear() // 모두 지워야(delete) 합니다.
    {
        while (first_) {
            PopFront();
        }
    }

    bool IsEmpty() {
        return first_ == nullptr;
    }

    int Size() {
        int size = 0;

        Node *current_node = first_;

        while (current_node) {
            size++;

            current_node = current_node->right;
        }

        return size;
    }

    void Print() {
        using namespace std;

        Node *current = first_;

        if (IsEmpty())
            cout << "Empty" << endl;
        else {
            cout << "Size = " << Size() << endl;

            cout << " Forward: ";
            // 정방향 출력
            while (true) {
                cout << current->item << " ";

                if (!current->right) break; // 제일 마지막 노드에서 정지

                current = current->right;
            }
            cout << endl; // 정방향 마지막 노드 출력

            cout << "Backward: ";
            // 역방향 출력
            while (true) {
                cout << current->item << " ";

                if (!current->left) break; // 제일 처음 노드에서 정지

                current = current->left;
            }
            cout << endl;
        }
    }

    Node *Find(T item) {
        Node *current_node = first_;

        while (current_node) {
            if (current_node->item == item) {
                return current_node;
            }

            current_node = current_node->right;
        }

        return nullptr;
    }

    void InsertBack(Node *node, T item) {
        if (IsEmpty()) {
            PushBack(item);
        } else {
            Node *new_node = new Node;
            new_node->item = item;
            new_node->left = node;
            new_node->right = node->right;

            if (node->right) node->right->left = new_node;
            node->right = new_node;
        }
    }

    void PushFront(T item) {
        Node *new_node = new Node;
        new_node->item = item;

        if (first_) {
            new_node->right = first_;
            first_->left = new_node;
            new_node->left = nullptr;
        }

        first_ = new_node;
    }

    void PushBack(T item) {
        Node *new_node = new Node;
        new_node->item = item;

        if (!first_) {
            first_ = new_node;
        } else {
            Node *current_node = first_;
            while (current_node->right) {
                current_node = current_node->right;
            }

            current_node->right = new_node;
            new_node->left = current_node;
        }
    }

    void PopFront() {
        if (IsEmpty()) {
            using namespace std;
            cout << "Nothing to Pop in PopFront()" << endl;
            return;
        }

        assert(first_);

        const Node *temp = first_;
        first_ = first_->right;
        first_->left = nullptr;

        delete temp;
    }

    void PopBack() {
        if (IsEmpty()) {
            using namespace std;
            cout << "Nothing to Pop in PopBack()" << endl;
            return;
        }

        assert(first_);

        Node *current_node = first_;

        if (current_node->right) {
            while (current_node->right->right) {
                current_node = current_node->right;
            }

            const Node *temp = current_node->right;
            current_node->right = nullptr;

            delete temp;
        } else {
            delete first_;
            first_ = nullptr;
        }
    }

    void Reverse() {
        Node *current_node = first_;
        Node *prev_node = nullptr;

        // Swap을 이용
        while (current_node) {
            // 보다 간결한 방법
            prev_node = current_node;
            current_node = current_node->right;

            std::swap(prev_node->left, prev_node->right);

            // 처음 구현했던 방법
            // Node *next_node = current_node->right;
            // current_node->right = current_node->left;
            // current_node->left = next_node;
            //
            // prev_node = current_node;
            // current_node = next_node;
        }

        first_ = prev_node; // 제일 마지막에 있던 Node가 first_로 변경
    }

    T Front() {
        assert(first_);

        return first_->item;
    }

    T Back() {
        assert(first_);

        Node *current_node = first_;
        while (current_node->right) {
            current_node = current_node->right;
        }

        return current_node->item;
    }

protected:
    Node *first_ = nullptr;
};
