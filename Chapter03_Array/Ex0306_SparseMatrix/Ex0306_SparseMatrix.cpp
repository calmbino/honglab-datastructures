#include <chrono>
#include <iostream>

#include "SparseMatrix.h"

int main() {
    using namespace std;

    SparseMatrix m1(4, 6, 6); // 4 by 6 matrix, Non-zero term 6개

    // 정렬되지 않은 순서로 추가
    m1.SetValue(2, 3, 5.0f);
    m1.SetValue(0, 5, 2.0f);
    m1.SetValue(1, 1, 1.0f);
    m1.SetValue(0, 0, 1.0f);
    m1.SetValue(0, 3, 7.0f);
    m1.SetValue(1, 2, 3.0f);

    m1.SetValue(2, 3, 4.0f); // <- 덮어쓰는 경우

    m1.PrintTerms();
    m1.Print();

    cout << endl;

    const SparseMatrix tr = m1.Transpose(); // 전치행렬

    tr.PrintTerms();
    tr.Print();

    cout << endl;


    cout << "----Transpose 메서드와 Transpose02 메서드의 성능차이 비교-----" << endl;

    // Transpose01 시간 측정
    auto start_time = std::chrono::high_resolution_clock::now(); // 시작 시간 기록
    SparseMatrix result1 = m1.Transpose(); // Transpose 함수 호출
    auto end_time = std::chrono::high_resolution_clock::now(); // 종료 시간 기록
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Transpose() 실행 시간: " << duration1 << " 마이크로초" << std::endl;

    // Transpose02 시간 측정
    start_time = std::chrono::high_resolution_clock::now(); // 시작 시간 기록
    SparseMatrix result2 = m1.Transpose02(); // Transpose02 함수 호출
    end_time = std::chrono::high_resolution_clock::now(); // 종료 시간 기록
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Transpose02() 실행 시간: " << duration2 << " 마이크로초" << std::endl;


    return 0;
}
