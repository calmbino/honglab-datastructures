#include <iostream>

#include "../../Shared/Stack.h"
#include "../../Shared/Queue.h"

using namespace std;

int Prec(char c); // 연산자 우선순위를 반환
void InfixToPostfix(Queue<char> &q, Queue<string> &output);

double EvalPostfix(Queue<string> &q);

/*
   infix: A/B-C+D*E-A*C
 postfix: AB/C-DE*+AC*-

   infix: 8 / 2 - 3 + 4 * 5 - 1 * 2 = 19
 postfix: 8 2 / 3 - 4 5 * + 1 2 * - // 연산자를 만날때까지 진행
		  = 4 3 - 4 5 * + 1 2 * -
		  = 1 4 5 * + 1 2 * -
		  = 1 20 + 1 2 * -
		  = 21 1 2 * -
		  = 21 2 -
		  = 19
*/

int main() {
	// 예제에서는 빈칸 없이 한 자리 숫자만 가능

	// constexpr char infix[] = "8/2+(3+4)*5-1*2";
	// constexpr char infix[] = "1+(1*2+3)*4";
	// constexpr char infix[] = "1+2*3+3";
	// constexpr char infix[] = "1+2*(3+1)";
	constexpr char infix[] = "-4+2.5*(3+1)-23*2";

	constexpr int size = sizeof(infix) / sizeof(char) - 1;

	// 큐에 모두 넣기
	Queue<char> q;
	for (int i = 0; i < size; i++)
		q.Enqueue(infix[i]);

	Queue<string> postfix;

	cout << "Infix: ";
	q.Print();
	cout << endl;

	InfixToPostfix(q, postfix);

	cout << "Postfix: ";
	postfix.Print();

	// const double result = EvalPostfix(postfix);

	cout << endl;
	cout << "Evaluated = " << EvalPostfix(postfix) << endl;

	return 0;
}

// 연산자 우선순위 반환 함수
int Prec(char c) {
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1; // '('는 우선순위가 아주 낮은 것으로 처리, ')' 닫는 괄호를 만날때까지 남겨두기 위함
}


void InfixToPostfix(Queue<char> &q, Queue<string> &output) {
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output.SetDebugFlag(false);

	string number; // 두 자릿수 이상의 정수, 소수 그리고 음수를 위한 버퍼
	bool expectNumber = true; // 숫자를 기대하는 상태인지 여부 (음수 판별에도 사용)

	while (!q.IsEmpty()) {
		const char c = q.Front();
		q.Dequeue();

		if ((c >= '0' && c <= '9') || c == '.') {
			// 숫자 및 소수점은 버퍼에 누적
			number += c;
		} else {
			// '-'를 음수 부호로 인식해야할 상황
			// 1) 전위 계산식에서 제일 첫 번째 문자가 '-'인 경우. (= number와 output 아무것도 없는 상황)
			// 2) '(' 다음에 '-'인 경우.
			if (c == '-' && ((number.empty() && output.IsEmpty()) || s.Top() == '(')) {
				number += c;
			} else {
				// 연산자를 만나면
				if (!number.empty()) {
					output.Enqueue(number); // 현재까지 누적된 숫자를 output에 추가
					number.clear(); // 버퍼 초기화
				}

				if (c == '(') {
					// 여는 괄호는 스택에 넣기
					s.Push(c);
				} else if (c == ')') {
					// 닫는 괄호라면
					while (s.Top() != '(') {
						// 스택에서 여는 괄호를 만날 때까지 모두 꺼내서 output에 넣기
						output.Enqueue(string(1, s.Top()));
						s.Pop();
					}
					s.Pop(); // 여는 괄호 꺼내기
				} else {
					// 스택에서 c(연산자)보다 우선순위가 높거나 같은 것들을 꺼내서 output에 추가
					while (!s.IsEmpty() && Prec(s.Top()) >= Prec(c)) {
						output.Enqueue(string(1, s.Top()));
						s.Pop();
					}
					// c는 스택에 추가
					s.Push(c);
				}
			}
		}

		cout << "Stack: ";
		s.Print();
		cout << "Output:";
		output.Print();
		cout << endl;
	}

	// 버퍼에 남아있는 숫자를 output에 추가
	if (!number.empty()) {
		output.Enqueue(number);
	}

	// 스택에 남아있는 것들을 모두 output에 추가
	while (!s.IsEmpty()) {
		output.Enqueue(string(1, s.Top()));
		s.Pop();
	}
}

double EvalPostfix(Queue<string> &q) {
	Stack<double> s;

	while (!q.IsEmpty()) {
		string token = q.Front();
		q.Dequeue();

		cout << token << endl;

		if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 || token.find('.') != string::npos)) {
			// 피연산자를 실수로 변환하여 스택에 추가
			s.Push(stod(token));
		} else {
			double numberB = s.Top();
			s.Pop();
			double numberA = s.Top();
			s.Pop();

			double result;
			if (token == "+") {
				result = numberA + numberB;
			} else if (token == "-") {
				result = numberA - numberB;
			} else if (token == "*") {
				result = numberA * numberB;
			} else if (token == "/") {
				result = numberA / numberB;
			} else {
				cout << "Wrong operator" << endl;
				exit(-1); // 강제 종료
			}

			s.Push(result);
		}

		cout << "Stack: ";
		s.Print();
	}

	return s.Top();
}
