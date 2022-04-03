#include "Matrix.hpp"
#include <cmath>

using std::cout;
using std::istream;
using std::ostream;

namespace zich
{

    int checkPositive(int k)
    {
        if (k <= 0)
        {
            throw "Invalid Dimensions!";
        }
        return k;
    }

    // If we got dimensions in int, cast to size_t
    Matrix::Matrix(vector<double> vals, int rows, int cols)
        : Matrix(std::move(vals), static_cast<size_t>(checkPositive(rows)), static_cast<size_t>(checkPositive(cols)))
    {
    }
    Matrix::Matrix(vector<double> mat, size_t rows, size_t columns) : rows{rows}, columns{columns}
    {
        if (mat.size() != rows * columns)
        {
            throw "Invalid Dimensions!";
        }

        for (int i = 0; i < rows; i++)
        {
            this->matrix.push_back(vector<double>(columns));
        }

        for (size_t i = 0; i < rows * columns; i++)
        {
            this->matrix.at(i / columns).at(i % columns) = mat.at(i);
        }
    }

    Matrix::Matrix(int rows, int columns)
    {
        if ((rows <= 0 || columns <= 0))
        {
            throw "Rows/Columns Must Be Positive Number!";
        }
        this->rows = static_cast<size_t>(rows);
        this->columns = static_cast<size_t>(columns);
        this->matrix.resize(static_cast<size_t>(rows));
        for (size_t i = 0; i < rows; i++)
        {
            this->matrix[i].resize(static_cast<size_t>(columns));
        }
    }

    // Copy Constructor
    Matrix::Matrix(const Matrix &mat)
        : rows{mat.rows}, columns{mat.columns}
    {
        this->matrix = mat.matrix;
    }

    Matrix::~Matrix()
    {
        for (unsigned int i = 0; i < this->rows; i++)
        {
            this->matrix[i].clear();
        }
        this->matrix.clear();
    }

    // Global Operators
    istream &operator>>(istream &in, const Matrix &mat)
    {
        return in;
    }
    ostream &operator<<(ostream &out, const Matrix &mat)
    {
        return out;
    }

    // Comparison Operators
    bool operator>(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }
    bool operator>=(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }

    bool operator<(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }
    bool operator<=(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }

    bool operator==(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }
    bool operator!=(const Matrix &mat1, const Matrix &mat2)
    {
        return false;
    }

    // Single Matrix Operators
    Matrix operator+(const Matrix &mat, double number)
    {
        return Matrix(2, 2);
    }
    Matrix operator+(double number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    Matrix operator+(const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    void operator+=(Matrix &mat, double number)
    {
    }

    Matrix operator-(const Matrix &mat, double number)
    {
        return Matrix(2, 2);
    }
    Matrix operator-(double number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    Matrix operator-(const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    void operator-=(Matrix &mat, double number)
    {
    }

    Matrix operator*(double number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    Matrix operator*(const Matrix &mat, double number)
    {
        return Matrix(2, 2);
    }
    void operator*=(Matrix &mat, double number)
    {
    }

    void operator++(Matrix &mat)
    {
    }
    void operator--(Matrix &mat)
    {
    }

    // Double Matrix Operators
    Matrix operator+(const Matrix &mat1, const Matrix &mat2)
    {
        return Matrix(2, 2);
    }
    void operator+=(Matrix &mat1, const Matrix &mat2)
    {
    }

    Matrix operator-(const Matrix &mat1, const Matrix &mat2)
    {
        return Matrix(2, 2);
    }
    void operator-=(Matrix &mat1, const Matrix &mat2)
    {
    }

    Matrix operator*(const Matrix &mat1, const Matrix &mat2)
    {
        return Matrix(2, 2);
    }
    void operator*=(Matrix &mat1, const Matrix &mat2)
    {
    }

    // Integer Operators
    Matrix operator+(const Matrix &mat, int number)
    {
        return Matrix(2, 2);
    }
    Matrix operator+(int number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    void operator+=(Matrix &mat, int number)
    {
    }

    Matrix operator-(const Matrix &mat, int number)
    {
        return Matrix(2, 2);
    }
    Matrix operator-(int number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    void operator-=(Matrix &mat, int number)
    {
    }

    Matrix operator*(int number, const Matrix &mat)
    {
        return Matrix(2, 2);
    }
    Matrix operator*(const Matrix &mat, int number)
    {
        return Matrix(2, 2);
    }
    void operator*=(Matrix &mat, int number)
    {
    }
}