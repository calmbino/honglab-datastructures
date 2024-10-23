## 성능 비교: Transpose() vs Transpose02() (with ChatGPT-4o)

두 함수의 **Big-O 시간 복잡도**를 분석하여 어느 함수가 더 효율적인지 계산해보았습니다. 각 함수의 주요 연산이 어떤 반복문을 사용하는지, 그리고 해당 반복문의 반복 횟수가 데이터 크기에 비례해 어떻게
증가하는지 살펴보자.

### 1. `Transpose()` 함수의 시간 복잡도:

```cpp
SparseMatrix SparseMatrix::Transpose() const {
    auto new_sparse_matrix = SparseMatrix(this->num_cols_, this->num_rows_, this->capacity_);

    for (int i = 0; i < this->num_terms_; i++) {
        new_sparse_matrix.SetValue(this->terms_[i].col, this->terms_[i].row, this->terms_[i].value);
    }

    return new_sparse_matrix;
}
```

#### 시간 복잡도 분석:

1. `for (int i = 0; i < this->num_terms_; i++)`:
    - 이 반복문은 희소 행렬에서 **0이 아닌 값의 개수**인 `num_terms_` 만큼 반복한다.
    - 즉, **`O(num_terms_)`**.

2. `SetValue(this->terms_[i].col, this->terms_[i].row, this->terms_[i].value)`:
    - `SetValue` 함수는 내부에서 **0이 아닌 값들을 삽입할 위치를 찾기 위해 선형 탐색**을 하고 있다.
    - 삽입 위치를 찾기 위한 탐색 과정은 **최악의 경우**에는 **`O(num_terms_)`** 시간이 걸린다.
    - 따라서, `SetValue`의 시간 복잡도는 **`O(num_terms_)`** 이다.

전체적으로 `Transpose()` 함수는 **`num_terms_`**번 반복하고, 각 반복에서 **`O(num_terms_)`** 시간이 걸리므로, 전체 시간 복잡도는:

- **`O(num_terms_ * num_terms_)`** = **`O(num_terms_^2)`**

### 2. `Transpose02()` 함수의 시간 복잡도:

```cpp
SparseMatrix SparseMatrix::Transpose02() const {
    auto new_sparse_matrix = SparseMatrix(this->num_cols_, this->num_rows_, this->capacity_);

    for (int r = 0; r < new_sparse_matrix.num_rows_; r++) {
        for (int i = 0; i < this->num_terms_; i++) {
            if (terms_[i].col == r) {
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].value = this->terms_[i].value;
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].col = this->terms_[i].row;
                new_sparse_matrix.terms_[new_sparse_matrix.num_terms_].row = this->terms_[i].col;
                new_sparse_matrix.num_terms_ += 1;
            }
        }
    }

    return new_sparse_matrix;
}
```

#### 시간 복잡도 분석:

1. `for (int r = 0; r < new_sparse_matrix.num_rows_; r++)`:
    - 이 반복문은 **행렬의 행의 개수**만큼 반복되므로 **`O(num_rows_)`** 이다.

2. `for (int i = 0; i < this->num_terms_; i++)`:
    - 이 내부 반복문은 **0이 아닌 값의 개수**인 `num_terms_` 만큼 반복된다.
    - 즉, **`O(num_terms_)`**.

3. `if (terms_[i].col == r)`:
    - 내부에서 **열 값 비교**를 한 번 수행하는 비교문이 있다. 이는 상수 시간이므로, 시간 복잡도에 큰 영향을 주지 않는다.

`Transpose02()` 함수의 전체 시간 복잡도는 **두 중첩 반복문**에 의해 결정된다:

- 외부 반복문은 **`O(num_rows_)`**이고, 내부 반복문은 **`O(num_terms_)`** 입니다.
- 전체 시간 복잡도는 **`O(num_rows_ * num_terms_)`**.

### 두 함수의 Big-O 비교:

- **`Transpose()`**:
    - **시간 복잡도**: `O(num_terms_^2)`
    - 이 함수는 **0이 아닌 값의 개수에 따라 제곱**에 비례하는 성능을 보인다. 즉, 0이 아닌 값의 개수가 증가할수록 **성능 저하**가 크다.

- **`Transpose02()`**:
    - **시간 복잡도**: `O(num_rows_ * num_terms_)`
    - 이 함수는 **행렬의 행 수**와 **0이 아닌 값의 개수**에 따라 선형적으로 성능이 저하된다. 만약 행의 개수가 크지 않고 0이 아닌 값의 개수가 상대적으로 적다면, **더 효율적** 이다.

### 결론:

- **`Transpose()`**는 **0이 아닌 값의 개수**에 따라 성능이 **제곱으로 증가**하기 때문에, 0이 아닌 값이 많아지면 성능이 급격히 떨어질 수 있다.
- **`Transpose02()`**는 **행렬의 행 수**와 **0이 아닌 값의 개수**에 비례하여 성능이 저하되므로, 더 효율적이다. 특히, 행의 개수가 너무 많지 않은 희소 행렬에서는 **
  `Transpose02()`**가 **더 나은 성능**을 보일 것이다.
- 실제 테스트에서는 행렬의 크기가 매우 작은 희소 행렬이기 때문에 성능차이는 거의 없었다. 행렬의 크기가 매우 커지면 성능차이가 뚜렷하게 나타난다.

  <img src="https://github.com/user-attachments/assets/98aa3929-4b30-47df-9202-b623c1f81159" alt="첫 번째 이미지" width="40%"/>
  <img src="https://github.com/user-attachments/assets/b2a23406-ed29-4f72-81a8-18e70bd3ee5a" alt="두 번째 이미지" width="40%"/>





