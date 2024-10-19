#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString() {
  str_ = nullptr;
  size_ = 0;
}

// 맨 뒤에 널 캐릭터('\0')가 들어있는 문자열로부터 초기화
MyString::MyString(const char *init) {
  size_ = 0;
  while (init[size_] != '\0') {
    size_++;
  }

  str_ = new char[size_ + 1]; // 글자 개수 + 널 문자 위한 메모리 공간 확보
  memcpy(str_, init, size_);
  str_[size_] = '\0'; // 널 문자 추가
}

// MyString의 다른 인스턴스로부터 초기화 (깊은 복사)
MyString::MyString(const MyString &str) {
  size_ = str.size_;
  str_ = new char[size_ + 1]; // 널 문자를 위한 공간 확보
  memcpy(str_, str.str_, size_);
  str_[size_] = '\0'; // 널 문자 추가
}

// 소멸자
MyString::~MyString() {
  // 메모리를 할당 받은적이 있는지 체크
  if (str_ != nullptr) {
    delete[] str_;
    str_ = nullptr; // 생략 가능
    size_ = 0; // 생략 가능
  }
}

// 비었는지 확인
bool MyString::IsEmpty() const {
  return this->Length() == 0; // 길이가 0이면 true
}

// 두 문자열이 같은지 확인
bool MyString::IsEqual(const MyString &str) const {
  if (str.Length() != this->Length()) {
    return false;
  }

  for (int i = 0; i < this->Length(); i++) {
    if (str.str_[i] != this->str_[i]) {
      return false;
    }
  }

  return true;
}

// 문자열의 길이 반환
int MyString::Length() const {
  return size_;
}

// 문자열의 크기 변경 (새로 할당)
void MyString::Resize(const int new_size) {
  if (new_size != size_) {
    const auto new_str = new char[new_size + 1]; // 널 문자를 위한 공간 추가

    // 새로운 사이즈가 기존 사이즈보다 작아지는 경우도 대비
    memcpy(new_str, str_, new_size < size_ ? new_size : size_);

    delete[] str_; // 기존 메모리는 삭제
    str_ = new_str; // 새로운 메모리의 포인터를 저장
    size_ = new_size;
    str_[size_] = '\0'; // 널 문자 추가
  }
}

// 부분 문자열 반환
MyString MyString::Substr(const int start, const int num) const {
  // 입력받은 start, num에 대하여 유효성 검사
  if (start < 0 || num < 0 || start + num > this->Length()) {
    throw out_of_range("Invalid start or length for Substr");
  }

  MyString new_str;
  new_str.Resize(num);

  for (int i = 0; i < num; i++) {
    new_str.str_[i] = this->str_[start + i];
  }

  new_str.str_[num] = '\0'; // 널 문자 추가

  return new_str;
}

// 문자열 결합
MyString MyString::Concat(const MyString &app_str) const {
  MyString new_str;
  new_str.Resize(this->Length() + app_str.Length());

  memcpy(new_str.str_, this->str_, this->Length());
  memcpy(&new_str.str_[this->Length()], app_str.str_, app_str.Length());

  new_str.str_[new_str.Length()] = '\0'; // 널 문자 추가

  return new_str;
}

// 문자열 삽입
MyString MyString::Insert(const MyString &t, const int start) const {
  if (start < 0 || start > this->Length()) {
    throw out_of_range("Invalid start for Insert");
  }

  MyString new_str;
  new_str.Resize(this->Length() + t.Length());

  memcpy(new_str.str_, this->str_, start);
  memcpy(&new_str.str_[start], t.str_, t.Length());
  memcpy(&new_str.str_[start + t.Length()], &this->str_[start], this->Length() - start);

  new_str.str_[new_str.Length()] = '\0'; // 널 문자 추가

  return new_str;
}

// 문자열 찾기
int MyString::Find(const MyString &pat) const {
  for (int start = 0; start <= this->Length() - pat.Length(); start++) {
    for (int j = 0; j < pat.Length(); j++) {
      // 한 글자라도 일치하지 않으면 start를 +1 증가한 후 다시 비교
      if (this->str_[start + j] != pat.str_[j]) {
        break;
      }

      // 모든 글자가 모두 일치하면 start 리턴
      if (j == pat.Length() - 1) {
        return start;
      }
    }
  }

  return -1;
}

// 문자열 출력
void MyString::Print() const {
  if (str_ != nullptr) {
    cout << str_ << endl;
  }
}
