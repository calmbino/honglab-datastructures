/*
 * ADT(Abstract Data Type, 추상 자료형)
 *
 * - 데이터와 그 데이터를 처리하는 연산들을 추상화한 개념이다.
 * - 자세한 구현 내용을 감추고, 사용자에게는 데이터를 다룰 수 있는 인터페이스만 제공한다.
 * - 모듈화, 유지보수성, 재사용성을 높이는데 도움을 준다.
 */

#pragma once // 헤더 파일이 한 번만 포함되도록 보장하는 전처리기 지시어

#include <iostream>
#include <cstring> // for memcpy
#include <stdexcept> // for out_of_range

class MyString {
public:
    MyString(); // 비어 있는 MyString() 생성
    explicit MyString(const char *init); // 맨 뒤에 null 캐릭터('\0')가 들어있는 문자열로부터 초기화
    MyString(const MyString &str); // MyString의 다른 인스턴스로부터 초기화
    ~MyString();

    [[nodiscard]] bool IsEmpty() const;

    [[nodiscard]] bool IsEqual(const MyString &str) const;

    [[nodiscard]] int Length() const;

    void Resize(int new_size);

    [[nodiscard]] MyString Substr(int start, int num) const; // 인덱스 start 위치의 글자부터 num개의 글자로 새로운 문자열 만들기
    [[nodiscard]] MyString Concat(const MyString &app_str) const; // 뒤에 덧붙인 새로운 문자열 반환 (= append)
    [[nodiscard]] MyString Insert(const MyString &t, int start) const; // 중간에 삽입

    int Find(const MyString &pat) const;

    void Print() const; // 불변성 보장 >> const 함수는 멤버 변수를 변경하지 않겠다는 명시적 약속이다.

private:
    char *str_ = nullptr; // 마지막에 '\0' 없음
    int size_ = 0; // 글자 수
};



