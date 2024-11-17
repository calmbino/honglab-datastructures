#include <iostream>

using namespace std;

struct Node {
    // Node가 저장할 데이터.
    // 문자열과 구조체 같은 큰 데이터 저장도 가능.
    int item = 0;

    // 현재 노드가 가리키는 다음 노드를 나타내는 포인터.
    Node *next = nullptr;


    // cout으로 Node를 간단하게 출력할 수 있도록 도와주는 함수.
    // Node 구조체에 대해 출력 연산자(<<)를 오버로딩하는 코드.
    // 출력 스트림(ostream)에 노드의 데이터를 형식화하여 출력할 수 있도록 설정.
    // "friend" 키워드는 클래스(또는 구조체) 외부에 정의된 함수가 해당 클래스의
    // private, protected 멤버에 접근할 수 있도록 허용.
    friend ostream &operator<<(ostream &os, const Node &n) {
        cout << "[" << &n << ", " << n.item << ", " << n.next << "]" << flush;
        return os;
    }
};

void RecurPrint(const Node *node) {
    if (node != nullptr) {
        cout << *node << " ";
        RecurPrint(node->next);
    }
}

void IterPrint(const Node *node) {
    const Node *current = node;

    while (current != nullptr) {
        cout << *current << " ";
        current = current->next;
    }
}

int main() {
    // ListArray와 비교

    Node *first = nullptr;
    first = new Node;
    first->item = 1;
    first->next = nullptr;

    Node *second = nullptr;
    second = new Node;
    second->item = 2;
    second->next = nullptr;

    Node *third = nullptr;
    third = new Node;
    third->item = 3;
    third->next = nullptr;

    Node *fourth = nullptr;
    fourth = new Node;
    fourth->item = 4;
    fourth->next = nullptr;

    Node *fifth = nullptr;
    fifth = new Node;
    fifth->item = 5;
    fifth->next = nullptr;

    // 계속 추가 가능

    cout << *first << endl;
    cout << *second << endl;
    cout << *third << endl;
    cout << *fourth << endl;
    cout << *fifth << endl;
    cout << endl;

    // 연결 관계 만들어 주기
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = nullptr;

    cout << *(first) << endl;
    cout << *(first->next) << endl;
    cout << *(first->next->next) << endl;
    cout << *(first->next->next->next) << endl;
    cout << *(first->next->next->next->next) << endl;
    // cout << *(first->next->next->next->next->next) << endl; // 오류

    cout << endl;

    // 임시 변수 사용
    {
        cout << "Print using temp variable: ";

        Node *current = first;
        cout << *current << " ";

        current = current->next;
        cout << *current << " ";

        current = current->next;
        cout << *current << " ";

        current = current->next;
        cout << *current << " ";

        current = current->next;
        cout << *current << " ";

        cout << endl;
        cout << endl;
    }

    // 재귀 호출 이용
    cout << "RecurPrint: ";
    RecurPrint(first);
    cout << endl;
    cout << endl;

    // 반복문 이용
    cout << "IterPrint: ";
    IterPrint(first);
    cout << endl;
    cout << endl;

    // 모든 노드 데이터 삭제
    {
        const Node *current = first;

        while (current != nullptr) {
            const Node *temp = current;

            cout << "Delete: " << *temp << endl;

            current = current->next;

            delete temp;
        }
    }

    return 0;
}
