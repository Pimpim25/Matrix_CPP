#include <stdbool.h>

#include <algorithm>
#include <cmath>

using namespace std;

class myMatrix {
 private:
  int rows_{0}, cols_{0};
  double** matrix_{nullptr};

 public:
  myMatrix() = default;
  myMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows_ < 1 || cols_ < 1) throw "Incorrect dimension of matrix";

    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  }
  myMatrix(const myMatrix& other) : myMatrix(other.rows_, other.cols_) {
    set_values(other.matrix_);
  }
  myMatrix(myMatrix&& other) noexcept
      : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  ~myMatrix() noexcept {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }

 private:
  void set_values(double** matrix) noexcept {
    if (matrix) {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          this->matrix_[i][j] = matrix[i][j];
        }
      }
    }
  }

 public:
  int get_rows() noexcept { return rows_; }
  int get_cols() noexcept { return cols_; }
  double** get_matrix_() noexcept { return matrix_; }
  void set_cols(int cols) { set_rows_cols(rows_, cols); }
  void set_rows(int rows) { set_rows_cols(rows, cols_); }
  void set_rows_cols(int rows, int cols);

  bool EqMatrix(const myMatrix& other);
  void SumMatrix(const myMatrix& other);
  void SubMatrix(const myMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const myMatrix& other);
  myMatrix Transpose();
  myMatrix CalcComplements();
  void CalcComplements_new_matrix(myMatrix* temp, int n_i, int n_j);
  double Determinant();
  void sort_matrix(myMatrix* ptr, double* sign, int k);
  myMatrix InverseMatrix();

  myMatrix operator+(const myMatrix& other);
  myMatrix operator-(const myMatrix& other);
  myMatrix operator*(const double num);
  myMatrix operator*(const myMatrix& other);
  bool operator==(const myMatrix& left) noexcept;
  myMatrix& operator=(const myMatrix& other) noexcept;
  myMatrix& operator=(myMatrix&& other) noexcept;
  myMatrix& operator+=(const myMatrix& other);
  myMatrix& operator-=(const myMatrix& other);
  myMatrix& operator*=(const myMatrix& other);
  myMatrix& operator*=(const double num) noexcept;
  double& operator()(int i, int j);
};