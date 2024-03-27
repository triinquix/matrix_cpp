#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  // Constructors
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // Parametrized constructor
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor

  // Destructor
  ~S21Matrix();

  // Operations
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix get_supporting_mat(int row, int column);
  S21Matrix InverseMatrix();

  // Getters
  int get_num_of_columns();
  int get_num_of_rows();

  // Setters
  void set_num_of_rows(int num_of_rows);
  void set_num_of_cols(int num_of_cols);

  // Operators
  S21Matrix operator+(S21Matrix& mat_1);
  S21Matrix operator-(S21Matrix& mat_1);
  S21Matrix operator*(S21Matrix& mat);
  friend S21Matrix operator*(double x, S21Matrix& mat);
  friend S21Matrix operator*(S21Matrix& mat, double x);
  bool operator==(S21Matrix& mat);
  void operator=(S21Matrix& mat);
  void operator+=(S21Matrix& mat);
  void operator-=(S21Matrix& mat);
  void operator*=(S21Matrix& mat);
  void operator*=(double x);
  double operator()(int i, int j);
  double* operator[](int i);
};

#endif