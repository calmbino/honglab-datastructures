#include "../../Shared/Queue.h"

#include <iostream>

using namespace std;

int main() {
    constexpr int n = 7;
    constexpr int k = 3; // set n and k to the desired values

    Queue<int> q(n + 1);
    q.SetDebugFlag(false);

    // 처음에 n명 추가 (1, 2, ..., n)
    for (int i = 1; i <= n; i++)
        q.Enqueue(i);
    q.Print();

    // 마지막 한 명이 남을 때까지 반복
    {
        while (q.Size() > 1) {
            // k-1 명은 맨 앞에서 뒤로 보내기
            for (int i = 0; i < k - 1; i++) {
                int safePerson = q.Front();
                q.Dequeue();
                q.Enqueue(safePerson);
            }

            q.Print();

            // k 번째 사람 처형
            const int killedPerson = q.Front();
            q.Dequeue();
            cout << "Executed " << killedPerson << endl;

            cout << endl;
            q.Print();
        }
    }

    // 최후의 생존자 번호
    cout << "Survivor: " << q.Rear() << endl;

    return 0;
}
