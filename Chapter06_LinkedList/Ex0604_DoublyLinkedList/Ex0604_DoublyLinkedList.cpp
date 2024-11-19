#include <iostream>

#include "../../Shared/DoublyLinkedList.h"

using namespace std;

int main() {
    DoublyLinkedList<int> list;

    list.Print();

    list.PushFront(3);
    list.Print();

    list.PushBack(4);
    list.Print();

    list.PushFront(2);
    list.Print();

    list.PushFront(1);
    list.Print();

    list.PushBack(5);
    list.Print();

    list.Reverse();
    list.Print();
    cout << endl;

    cout << "복사생성자 테스트" << endl;
    DoublyLinkedList<int> list2(list);
    list2.Print();
    cout << endl;

    cout << "Find() 및 InsertBack() 테스트" << endl;
    DoublyLinkedList<int>::Node *temp = list.Find(3);
    list.InsertBack(temp, 1000);
    list.Print();
    cout << endl;

    cout << "PopFront()/PopBack() 및 Clear() 테스트" << endl;
    for (int i = 0; i < 5; i++) {
        // list.Clear();

        // list.PopFront();
        // list.Print();

        list.PopBack();
        list.Print();

        if (!list.IsEmpty())
            cout << "Front: " << list.Front() << ", Back: " << list.Back() << endl;
    }

    // Edge case 테스트 주의
    return 0;
}
