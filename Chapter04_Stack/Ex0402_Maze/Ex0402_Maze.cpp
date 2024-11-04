#include <iostream>

#include "../../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

char maze[kNumRows][kNumCols] =
{
    {'1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '0', '1', '0', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
    {'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};


/**
 * 미로 출력용
 */
void PrintMaze() {
    for (int j = 0; j < kNumRows; j++) {
        for (int i = 0; i < kNumCols; i++)
            cout << maze[j][i] << " ";
        cout << endl;
    }
}

/**
 * [참고] range-based for loop를 이용한 출력 방식
 */
// void PrintMaze() {
//     for (const auto &row: maze) {
//         // 각 행을 가져옴
//         for (const auto &cell: row) {
//             // 각 행의 각 셀을 가져옴
//             cout << cell << " ";
//         }
//         cout << endl;
//     }
// }

/**
 * 2차원 좌표
 */
struct Pos {
    int row;
    int col;

    // 디버깅을 위한 편의 기능
    // ex)
    // Pos p1 = {3,4}
    // cout << p1 << endl;
    // 출력 결과: (3, 4)
    friend ostream &operator<<(ostream &os, const Pos &pos) {
        cout << "(" << pos.row << ", " << pos.col << ")" << flush;
        return os;
    }
};

/**
 * [풀이01] 재귀를 이용한 미로 찾기
 */
void RecurMaze(const Pos p) {
    const char mark = maze[p.row][p.col];

    if (mark == 'G') {
        cout << "Found!" << endl;
        return;
    }

    if (mark == '1' || mark == 'X') { return; }

    // 상,하,좌,우 이동
    constexpr int moveRow[] = {-1, 1, 0, 0};
    constexpr int moveCol[] = {0, 0, -1, 1};

    maze[p.row][p.col] = 'X';

    for (int i = 0; i < 4; i++) {
        RecurMaze({p.row + moveRow[i], p.col + moveCol[i]});
    }
}

/**
 * [풀이02] 재귀를 이용한 미로 찾기 (조기 종료가 가능한 버전)
 */
int RecurMazeEarlyExit(Pos p) {
    const char mark = maze[p.row][p.col];

    if (mark == 'G') {
        cout << "Found!" << endl;
        return 1;
    }

    if (mark == '1' || mark == 'X') { return 0; }

    // 상,하,좌,우 이동
    constexpr int moveRow[] = {-1, 1, 0, 0};
    constexpr int moveCol[] = {0, 0, -1, 1};

    maze[p.row][p.col] = 'X';

    // 현재는 상->하->좌->우 순서대로 탐색을 진행하는데,
    // 탐색 순서에 따라 목표 지점을 찾는 속도가 크게 달라진다.
    for (int i = 0; i < 4; i++) {
        if (RecurMazeEarlyExit({p.row + moveRow[i], p.col + moveCol[i]})) { return 1; }
    }

    return 0;
}

/**
 * [풀이03] Stack을 이용한 미로 찾기
 */
void StackMaze() {
    Stack<Pos> s;

    Pos start = {1, 1}; // i = 1, j = 1  시작 지점
    s.Push(start);

    // s.Print(); // 디버깅에 사용 가능

    while (!s.IsEmpty()) {
        Pos p = s.Top();
        s.Pop();

        cout << p << " "; // 디버깅 출력

        const char mark = maze[p.row][p.col];

        if (mark == 'G') {
            cout << "Found!" << endl;
            break;
        }

        if (mark == '1' || mark == 'X') { continue; }

        maze[p.row][p.col] = 'X';

        // 상,하,좌,우 이동
        // stack에 넣을 때는 상->하->좌->우 순서이지만
        // 실제로 꺼내서 확인하는 것은 반대 순서인 우->좌->하->상 이다.
        // 그래서 재귀(풀이2) 방식과 비교해보면 탐색경로가 다르다는 것을 볼 수 있다.
        constexpr int moveRow[] = {-1, 1, 0, 0};
        constexpr int moveCol[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            s.Push({p.row + moveRow[i], p.col + moveCol[i]});
        }
    }
}

int main() {
    PrintMaze();

    cout << endl;

    // RecurMaze({1, 1});

    RecurMazeEarlyExit({1, 1});

    // StackMaze();


    cout << endl;

    PrintMaze();

    return 0;
}
