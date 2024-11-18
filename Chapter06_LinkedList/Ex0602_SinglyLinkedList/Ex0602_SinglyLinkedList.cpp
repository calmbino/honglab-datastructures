#include <iostream>

#include "../../Shared/SinglyLinkedList.h"

using namespace std;

int main() {
    SinglyLinkedList<int> list;

    list.SetPrintDebug(true);

    list.PushFront(3);
    list.PushBack(4);
    list.PushFront(2);
    list.PushFront(1);
    list.PushBack(5);

    // list.Clear();

    list.Print();

    // copy constructor
    {
        SinglyLinkedList<int> list2 = list; // copy constructor
        list2.SetPrintDebug(true);
        list2.Print();
    }

    list.Reverse();
    list.Print();

    SinglyLinkedList<int>::Node *temp = list.Find(1);
    list.InsertBack(temp, 1000);
    list.Print();


    list.InsertBack(temp, 50);
    list.Print();
    list.Remove(temp);
    list.Print();

    // PopFront()/Back() 테스트
    for (int i = 0; i < 5; i++) {
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
