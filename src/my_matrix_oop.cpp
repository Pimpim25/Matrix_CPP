#include "my_matrix_oop.h"

bool myMatrix::EqMatrix(const myMatrix& other) {
  if (other.rows_ == this->rows_ && other.cols_ == this->cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(other.matrix_[i][j] - this->matrix_[i][j]) > 1.e-7)
          return false;
      }
    }
    return true;
  } else
    return false;
};

void myMatrix::SumMatrix(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "SumMatrix: Different sizes of matrices.";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
};
void myMatrix::SubMatrix(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "SubMatrix: Different sizes of matrices.";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
};
void myMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
};
void myMatrix::MulMatrix(const myMatrix& other) {
  if (cols_ != other.rows_) throw "Incompatible matrix sizes";

  if (other.matrix_ && matrix_) {
    double** temp_matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      temp_matrix_[i] = new double[other.cols_]();
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        for (int k = 0; k < cols_; k++) {
          temp_matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }

    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    cols_ = other.cols_;
    matrix_ = temp_matrix_;
  }
};
myMatrix myMatrix::Transpose() {
  myMatrix a;
  if (rows_ && cols_) a.set_rows_cols(this->cols_, this->rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      a.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return a;
};
myMatrix myMatrix::CalcComplements() {
  if (rows_ != cols_) throw "CalcComplements: rows is not equal to cols.";
  myMatrix res;
  if (rows_ == 1) {
    res.set_rows_cols(1, 1);
    res(0, 0) = 1;
  } else if (rows_ > 1 && cols_ > 1) {
    res.set_rows_cols(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        myMatrix temp(rows_ - 1, cols_ - 1);
        CalcComplements_new_matrix(&temp, i, j);
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
        res(i, j) = sign * temp.Determinant();
      }
    }
  }
  return res;
};
void myMatrix::CalcComplements_new_matrix(myMatrix* temp, int n_i, int n_j) {
  int l{}, k{};
  for (int i = 0; i < rows_; ++i) {
    if (i == n_i) continue;
    k = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == n_j) continue;
      temp->matrix_[l][k] = matrix_[i][j];
      k++;
    }
    l++;
  }
}
double myMatrix::Determinant() {
  if (rows_ != cols_) throw "Determinant: rows is not equal to cols.";
  if (rows_ == 1) return matrix_[0][0];
  double res{};
  if (rows_ > 1) {
    myMatrix temp(rows_, cols_);
    myMatrix* ptr = this;
    double sign{1.}, d{1.};
    for (int k = 0; k < rows_ - 1; k++) {
      if (fabs(ptr->matrix_[k][k]) < 1.e-7) sort_matrix(ptr, &sign, k);
      if (fabs(ptr->matrix_[k][k]) < 1.e-7) return 0.;
      for (int i = k + 1; i < rows_; ++i) {
        for (int j = k + 1; j < cols_; ++j) {
          temp.matrix_[i][j] = (ptr->matrix_[k][k] * ptr->matrix_[i][j] -
                                ptr->matrix_[i][k] * ptr->matrix_[k][j]) /
                               d;
        }
      }
      d = ptr->matrix_[k][k];
      ptr = &temp;
    }
    res = sign * ptr->matrix_[rows_ - 1][cols_ - 1];
  }
  return res;
};
void myMatrix::sort_matrix(myMatrix* ptr, double* sign, int k) {
  int l = k + 1;
  while (l < rows_ && fabs(ptr->matrix_[l][k]) < 1.e-7) {
    ++l;
  }
  if (l == rows_) return;
  *sign *= -1.0;

  for (int j = 0; j < cols_; j++) {
    swap(ptr->matrix_[k][j], ptr->matrix_[l][j]);
  }
};
myMatrix myMatrix::InverseMatrix() {
  try {
    double det = Determinant();
    if (fabs(det) < 1.e-7) throw "InverseMatrix: determinant is 0.";
    myMatrix a(*this);
    a = a.CalcComplements();
    a = a.Transpose();
    a *= (1. / det);
    return a;
  } catch (const char* msg) {
    throw msg;
  }
};

void myMatrix::set_rows_cols(int rows, int cols) {
  if (rows < 1 || cols < 1) throw "Incorrect dimension of matrix";
  double** temp_matrix_ = new double*[rows]();
  for (int i = 0; i < rows; i++) {
    temp_matrix_[i] = new double[cols]();
  }
  int temp_rows = min(rows, rows_), temp_cols = min(cols, cols_);
  for (int i = 0; i < temp_rows; ++i) {
    for (int j = 0; j < temp_cols; ++j) {
      temp_matrix_[i][j] = matrix_[i][j];
    }
  }
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = rows;
  cols_ = cols;
  matrix_ = temp_matrix_;
};

myMatrix myMatrix::operator+(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "operator+: Different sizes of matrices.";
  myMatrix a(*this);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      a.matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return a;
}

myMatrix myMatrix::operator-(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "operator-: Different sizes of matrices.";
  myMatrix a(*this);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      a.matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return a;
}

myMatrix myMatrix::operator*(const double num) {
  myMatrix a(*this);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      a.matrix_[i][j] *= num;
    }
  }
  return a;
}

myMatrix myMatrix::operator*(const myMatrix& other) {
  if (cols_ != other.rows_) throw "Incompatible matrix sizes";
  myMatrix a(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; k++) {
        a.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return a;
}

myMatrix& myMatrix::operator=(const myMatrix& other) noexcept {
  if (this != &other) {
    if (matrix_) {
      for (int i = 0; i < rows_; i++) delete[] matrix_[i];
      delete[] matrix_;
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    set_values(other.matrix_);
  }
  return *this;
}

myMatrix& myMatrix::operator=(myMatrix&& other) noexcept {
  if (this != &other) {
    if (matrix_) {
      for (int i = 0; i < rows_; i++) delete[] matrix_[i];
      delete[] matrix_;
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

myMatrix& myMatrix::operator+=(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "operator+=: Different sizes of matrices.";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

myMatrix& myMatrix::operator-=(const myMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "operator-=: Different sizes of matrices.";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

myMatrix& myMatrix::operator*=(const myMatrix& other) {
  if (cols_ != other.rows_) throw "Incompatible matrix sizes";
  double** temp_matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    temp_matrix_[i] = new double[other.cols_]();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; k++) {
        temp_matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  cols_ = other.cols_;
  matrix_ = temp_matrix_;
  return *this;
}

myMatrix& myMatrix::operator*=(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
  return *this;
}

double& myMatrix::operator()(int i, int j) {
  if (i < 0 || i > rows_ - 1 || j < 0 || j > cols_ - 1)
    throw "operator(): Invalid values";
  return matrix_[i][j];
}

bool myMatrix::operator==(const myMatrix& left) noexcept {
  if (rows_ != left.rows_ || cols_ != left.cols_) return false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(left.matrix_[i][j] - matrix_[i][j]) > 1.e-7) return false;
    }
  }
  return true;
}