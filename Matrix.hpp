#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::istream;
using std::ostream;
using std::vector;

namespace zich
{
    class Matrix
    {
    private:
        size_t rows;
        size_t columns;
        vector<vector<double>> matrix;

    public:
        // Constructors
        Matrix(vector<double> mat, size_t rows, size_t columns);
        Matrix(vector<double> mat, int rows, int columns);
        Matrix(const Matrix &mat);
        Matrix(int rows, int columns);

        // Destructor
        ~Matrix();

        // Global Operators
        friend istream &operator>>(istream &in, const Matrix &mat);
        friend ostream &operator<<(ostream &out, const Matrix &mat);

        // Comparison Operators
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);

        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);

        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);

        // Single Matrix Operators
        friend Matrix operator+(const Matrix &mat, double number);
        friend Matrix operator+(double number, const Matrix &mat);
        friend Matrix operator+(const Matrix &mat);
        friend void operator+=(Matrix &mat, double number);

        friend Matrix operator-(const Matrix &mat, double number);
        friend Matrix operator-(double number, const Matrix &mat);
        friend Matrix operator-(const Matrix &mat);
        friend void operator-=(Matrix &mat, double number);

        friend Matrix operator*(double number, const Matrix &mat);
        friend Matrix operator*(const Matrix &mat, double number);
        friend void operator*=(Matrix &mat, double number);

        friend void operator++(Matrix &mat);
        friend void operator--(Matrix &mat);

        // Double Matrix Operators
        friend Matrix operator+(const Matrix &mat1, const Matrix &mat2);
        friend void operator+=(Matrix &mat1, const Matrix &mat2);

        friend Matrix operator-(const Matrix &mat1, const Matrix &mat2);
        friend void operator-=(Matrix &mat1, const Matrix &mat2);

        friend Matrix operator*(const Matrix &mat1, const Matrix &mat2);
        friend void operator*=(Matrix &mat1, const Matrix &mat2);

    };
};