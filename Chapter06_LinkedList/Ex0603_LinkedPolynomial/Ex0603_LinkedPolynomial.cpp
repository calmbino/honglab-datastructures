#include <cmath>
#include <iostream>
#include "../../Shared/SinglyLinkedList.h"

using namespace std;

struct Term {
	float coef;
	int exp;

	// 비교 연산자
	bool operator==(const Term &) const = default;
};

class LinkedPolynomial : public SinglyLinkedList<Term> {
public:
	typedef SinglyLinkedList<Term>::Node Node;

	void NewTerm(const float coef, const int exp) {
		Term *new_term = new Term(coef, exp);
		Node *current_node = first_;

		// 최초 추가 또는 최고차항보다 큰 경우
		if (!current_node || Back().exp < exp) {
			PushBack(*new_term);

			return;
		}

		// 최저차항보다 작은 경우
		if (Front().exp > exp) {
			PushFront(*new_term);

			return;
		}

		// 순회하면서 동일한 차수의 항이 있으면 더하기, 없으면 오름차순에 맞게 추가
		while (current_node) {
			auto [c_coef, c_exp] = current_node->item;

			// 동일한 차수의 항을 찾은 경우, 계수만 더해주고 종료.
			if (exp == c_exp) {
				current_node->item.coef = coef + c_coef;

				// 계수가 0이 되는 경우, 해당 차수의 행은 삭제.
				if (current_node->item.coef == 0) {
					Remove(current_node);
				}

				return;
			}

			// 오름차순 정렬을 위해 다음 차수 항이 존재하는지 확인
			if (current_node->next) {
				auto [n_coef, n_exp] = current_node->next->item;

				// 현재 항의 차수보다 크고 다음 항의 차수보다 작으면 추가 후 종료
				if (c_exp < exp && n_exp > exp) {
					InsertBack(current_node, *new_term);

					return;
				}
			}


			current_node = current_node->next;
		}
	}

	[[nodiscard]] float Eval(const float x) const {
		float temp = 0.0f;

		Node *current_node = first_;

		while (current_node) {
			auto [coef, exp] = current_node->item;

			temp += pow(x, static_cast<float>(exp)) * coef;

			current_node = current_node->next;
		}

		return temp;
	}

	[[nodiscard]] LinkedPolynomial Add(const LinkedPolynomial &poly) const {
		// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
		// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

		LinkedPolynomial temp;

		Node *i = this->first_;
		Node *j = poly.first_;


		while (i) {
			auto [coef, exp] = i->item;

			temp.NewTerm(coef, exp); // 오름차순으로 자동 정렬 및 덧셈 처리

			i = i->next;
		}

		while (j) {
			auto [coef, exp] = j->item;

			temp.NewTerm(coef, exp); // 오름차순으로 자동 정렬 및 덧셈 처리

			j = j->next;
		}


		return temp;
	}

	void Print() const {
		bool is_first = true; // 더하기 출력시 확인용

		const Node *current_node = first_;

		while (current_node) {
			auto [coef, exp] = current_node->item;

			if (!is_first) {
				cout << " + ";
			}

			cout << coef;

			if (exp != 0) {
				cout << "x^ " << exp;
			}

			is_first = false;
			current_node = current_node->next;
		}

		cout << endl;
	}

private:
};

int main() {
	using namespace std;

	LinkedPolynomial p1;

	// exp가 작은 항부터 추가한다고 가정
	p1.NewTerm(1.0f, 0); // 1 * x^0 = 1
	p1.NewTerm(1.5f, 1); // 1.5 * x^1
	p1.NewTerm(2.0f, 2); // 2 * x^2

	p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	cout << p1.Eval(0.0f) << endl; // 1 + 1.5*0 + 2*0^2 = 1
	cout << p1.Eval(1.0f) << endl; // 1 + 1.5*1 + 2*1^2 = 4.5
	cout << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

	cout << endl;

	// Add() Test1
	cout << "Add() Test" << endl; {
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(5.0f, 7);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11

		cout << endl;
	}

	// Add() Test2
	cout << "Add() Test2" << endl; {
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);
		p1.NewTerm(5.0f, 7);
		p1.NewTerm(3.5f, 10);
		p1.NewTerm(5.5f, 20);
		p1.NewTerm(5.0f, 1000);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(3.2f, 0);
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11 + 5.5*x^20 + 5*x^1000

		cout << endl;
	}

	return 0;
}
