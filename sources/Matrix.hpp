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
        Matrix(vector<double> mat, int rows, int columns);
        Matrix(vector <vector<double>> mat, int rows, int columns);
        Matrix(const Matrix &mat);
        Matrix(int rows, int columns);
        Matrix();

        // Destructor
        ~Matrix();

        // Friend functions
        friend ostream &operator<<(ostream &out, const Matrix &mat);
        friend istream &operator>>(istream &in, Matrix &mat);
        friend Matrix operator*(double scalar, const Matrix &mat);

        // Matrix with Matrix operations
        Matrix operator+(const Matrix &mat) const;
        Matrix operator-(const Matrix &mat) const;
        Matrix operator*(const Matrix &mat) const;
        Matrix operator+=(const Matrix &mat);
        Matrix operator-=(const Matrix &mat);
        Matrix operator*=(const Matrix &mat);

        // Matrix with scalars
        Matrix operator*(const double &scalar);
        Matrix operator*=(const double &scalar);

        // Matrix comparisons
        bool operator<(const Matrix &mat) const;
        bool operator<=(const Matrix &mat) const;
        bool operator>(const Matrix &mat) const;
        bool operator>=(const Matrix &mat) const;
        bool operator==(const Matrix &mat) const;
        bool operator!=(const Matrix &mat) const;

        // Matrix Unary Operators
        Matrix operator+();
        Matrix operator-();

        // Matrix Increment
        Matrix operator++(int num);    
        Matrix& operator++();           
        Matrix operator--(int num);    
        Matrix& operator--();           

        // Helpers
        bool dim_check(const Matrix &mat) const;
        double mat_sum(const Matrix &mat) const;
        size_t getRows();
    };
};