// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>


class Matrix {
protected:
    int rows = 3, cols = 4;
    double* x = nullptr;
public:
    double get(size_t index) {
        return x[index];
    }
    void set(size_t index, double value) {
        x[index] = value;
    }

    Matrix() {
        x = new double[rows * cols] {0};
    }

    Matrix(const Matrix& v) {
        this->rows = v.rows;
        this->cols = v.cols;
        x = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            x[i] = v.x[i];
        }
    }

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        x = new double[rows * cols] {0};
        std::cout << "first elem try " << x[0] << "\n";

    }

    double& operator()(int i, int j) {// обращение по 2 индексам
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            std::cerr << "error 1!\n";
            exit(1);
        }
        return x[i * cols + j];
    }
    

    double& operator[](int i) const { //обращение по одному индексу
        if (i < 0 || i >= rows) {
            std::cerr << "error 2!\n";
            exit(1);
        }
        return x[i];
    }

    Matrix& operator=(const Matrix& p) {
        this->rows = p.rows;
        this->cols = p.cols;
        if (rows != p.rows || cols != p.cols || p.cols == 0 || p.rows == 0) {
            x = new double[rows * cols];
        }
        else {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    x[i * cols + j] = p[i * cols + j];
                }
            }
        }
        delete[]x;
        return (*this);
    }

    ~Matrix() {
        std::cout << "~Matrix\n";
        if (x != nullptr) {
            delete[]x;
        }
    }
    void Print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << x[i * cols + j] << "  "; //ширина поля, колво знаков после запятой
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    Matrix Transpose() {
        Matrix transposed(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed(j, i) = (*this)(i, j);//обращние к элементу текцщей матрицы, копирование
            }
        }
        return transposed;
    }
};

class SquareMatrix : public Matrix {
public:
    SquareMatrix(int n) : Matrix(n, n) {};

    SquareMatrix operator+(const Matrix& p) const {
        SquareMatrix sum(rows);
        Matrix copy_old = p;
        for (int i = 0; i < rows*rows; i++) {
            sum.set(i, x[i] + copy_old.get(i));
        }
        return sum;
    }
    ~SquareMatrix() {
        std::cout << "~SquareMatrix";
    }
};


int main()
{
    Matrix a{ 3, 4 };
    a(0, 1) = 2.6;
    a.Print();

    Matrix b = a.Transpose();
    b.Print();


    SquareMatrix m1(5);
    m1[2] = 4;
    SquareMatrix m2(5);
    m2(3, 2) = 34;
    SquareMatrix sm = m1 + m2;

    sm.Print();
	return 0;
}
