#include "MyString.h"

using namespace std;

int main() {
  // 생성자, MyString::Print()
  {
    const MyString str1("hi hay he hel hello llo ello el el o!");
    str1.Print();
  }

  // Find()
  {
    const MyString str1("hi hay he hel hello llo ello el el o!");
    cout << str1.Find(MyString("hell")) << endl;

    cout << "Found at " << MyString("ABCDEF").Find(MyString("A")) << endl;
    cout << "Found at " << MyString("ABCDEF").Find(MyString("AB")) << endl;
    cout << "Found at " << MyString("ABCDEF").Find(MyString("CDE")) << endl;
    cout << "Found at " << MyString("ABCDEF").Find(MyString("EF")) << endl;
    cout << "Found at " << MyString("ABCDEF").Find(MyString("EFG")) << endl;
    cout << "Found at " << MyString("ABCDEF").Find(MyString("EFGHIJ")) << endl;
  }

  // 복사 생성자
  {
    const MyString str1("hi hay he hel hello llo ello el el o!");
    const MyString str2 = str1; // NOLINT(*-unnecessary-copy-initialization)
    // MyString str2(str1); (두 방식은 동일하게 복사 생성자로 동작한다)

    // 포인터 주소가 다르다는 것을 확인할 수 있다.
    cout << "str1 address: " << &str1 << endl;
    cout << "str2 address: " << &str2 << endl;

    str2.Print();
  }

  // IsEqual()
  {
    const MyString str3("Hello, World!");
    cout << boolalpha;
    cout << str3.IsEqual(MyString("Hello, World!")) << endl;
    cout << str3.IsEqual(MyString("Hay, World!")) << endl;
  }

  // Insert()
  {
    const MyString str4("ABCDE");
    for (int i = 0; i <= str4.Length(); i++) {
      MyString str5 = str4.Insert(MyString("123"), i);
      str5.Print();
    }
  }

  // Substr()
  {
    const MyString str("ABCDEFGHIJ");

    str.Substr(3, 4).Print();
  }

  // Concat()
  {
    const MyString str1("Hello, ");
    const MyString str2("World!");

    const MyString str3 = str1.Concat(str2);

    str3.Print();
  }

  return 0;
}
