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
        Matrix(const vector<double> mat, size_t rows, size_t columns);
        Matrix(const vector<vector<double>> mat, size_t rows, size_t columns);
        Matrix(const vector<double> mat, int rows, int columns);
        Matrix(const vector <vector<double>>mat, int rows, int columns);
        Matrix(const Matrix &mat);
        Matrix(int rows, int columns);
        Matrix();

        // Destructor
        ~Matrix();

        // Friend functions
        friend ostream &operator<<(ostream &out, const Matrix &mat);
        friend void operator>>(istream &in, const Matrix &mat);
        friend Matrix operator*(double num, const Matrix mat);

        // Matrix with Matrix operations
        Matrix &operator+(const Matrix &mat) const;
        Matrix &operator-(const Matrix &mat) const;
        Matrix &operator*(const Matrix &mat) const;
        Matrix &operator+=(const Matrix &mat);
        Matrix &operator-=(const Matrix &mat);
        Matrix &operator*=(const Matrix &mat);

        // Matrix with scalars
        Matrix &operator*(const double &scalar);
        Matrix &operator*=(const double &scalar);

        // Matrix comparisons
        bool &operator<(const Matrix &mat) const;
        bool &operator<=(const Matrix &mat) const;
        bool &operator>(const Matrix &mat) const;
        bool &operator>=(const Matrix &mat) const;
        bool &operator==(const Matrix &mat) const;
        bool &operator!=(const Matrix &mat) const;

        // Matrix Unary Operators
        Matrix &operator+();
        Matrix &operator-();

        // Matrix Increment
        Matrix &operator++(int num);    //matrix++
        Matrix &operator++();           //++matrix
        Matrix &operator--(int num);    //matrix--
        Matrix &operator--();           //--matrix

        // Helpers
        bool inline dim_check(const Matrix &mat) const;
    };
};