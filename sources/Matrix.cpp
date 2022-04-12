#include "Matrix.hpp"
#include <cmath>

using std::istream;
using std::move;
using std::ostream;

namespace zich
{
    bool flag = true;

    ostream &operator<<(ostream &out, const Matrix &mat)
    {
        return out;
    }

    void operator>>(istream &in, const Matrix &mat)
    {
    }

    Matrix operator*(double num, const Matrix &mat)
    {
        return mat;
    }

    bool Matrix::dim_check(const Matrix &mat) const
    {
        bool status = false;
        if (rows == mat.rows && columns == mat.columns)
        {
            return !status;
        }
        return status;
    }
    // If we get dimension in int, cast to size_t
    Matrix::Matrix(vector<double> mat, int rows, int columns) : rows{static_cast<size_t>(rows)}, columns{static_cast<size_t>(columns)}
    {
        if (rows <= 0 || columns <= 0)
        {
            throw "Invalid Arguments!";
        }
        if (mat.size() != rows * columns)
        {
            throw "Invalid Arguments!";
        }

        vector<vector<double>> matr(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows * columns; i++)
        {
            matr.at(i / static_cast<size_t>(columns)).at(i % static_cast<size_t>(columns)) = mat.at(i);

            this->matrix = matr;
            this->rows = static_cast<size_t>(rows);
            this->columns = static_cast<size_t>(columns);
        }
    }

    // If we get dimension in int, cast to size_t
    Matrix::Matrix(vector<vector<double>> mat, int rows, int columns) : rows{static_cast<size_t>(rows)}, columns{static_cast<size_t>(columns)}
    {

        if (rows <= 0 || columns <= 0)
        {
            throw "Invalid Arguments!";
        }

        vector<vector<double>> matr(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                matr.at(i).at(j) = mat.at(i).at(j);
            }
        }

        this->matrix = matr;
        this->rows = static_cast<size_t>(rows);
        this->columns = static_cast<size_t>(columns);
    }

    Matrix::Matrix(int rows, int columns)
    {
        if (rows <= 0 || columns <= 0)
        {
            throw "Invalid Arguments!";
        }
        vector<vector<double>> mat(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        this->matrix = mat;
        this->rows = static_cast<size_t>(rows);
        this->columns = static_cast<size_t>(columns);
    }

    // Copy Constructor
    Matrix::Matrix(const Matrix &mat)
        : rows{mat.rows}, columns{mat.columns}
    {
        this->matrix = mat.matrix;
    }

    Matrix::~Matrix()
    {
        for (size_t i = 0; i < this->rows; i++)
        {
            this->matrix.at(i).clear();
        }
        this->matrix.clear();
    }

    Matrix &Matrix::operator+(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }

        const vector<vector<double>> &vector1 = mat.matrix;
        const vector<vector<double>> &vector2 = this->matrix;
        size_t rows = mat.rows;
        size_t columns = mat.columns;

        vector<vector<double>> values(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                values.at(i).at(j) = vector1.at(i).at(j) + vector2.at(i).at(j);
            }
        }
        Matrix *resault = new Matrix(values, (int)rows, (int)columns);
        return *resault;
    }

    Matrix &Matrix::operator-(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }
        const vector<vector<double>> &vector1 = mat.matrix;
        const vector<vector<double>> &vector2 = this->matrix;
        size_t rows = mat.rows;
        size_t columns = mat.columns;

        vector<vector<double>> values(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                values.at(i).at(j) = vector1.at(i).at(j) - vector2.at(i).at(j);
            }
        }
        Matrix *resault = new Matrix(values, (int)rows, (int)columns);
        return *resault;
    }

    Matrix &Matrix::operator*(const Matrix &mat) const
    {
        if (this->columns != mat.rows)
        {
            throw "Multiplication Not Defined For These Dimension";
        }
        // Standard matrix multiplication algorith, done in O(n^3) to avoid implementing Strassen multiplication algorithm

        double running_sum = 0; // needed for calculations in matrix multiplication
        vector<vector<double>> values;
        for (size_t i = 0; i < this->rows; i++)
        {
            values.emplace_back(vector<double>(mat.columns, 0));
            for (size_t j = 0; j < mat.columns; j++)
            {
                running_sum = 0;

                for (size_t k = 0; k < mat.rows; k++)
                {
                    running_sum += this->matrix.at(i).at(k) * mat.matrix.at(k).at(j);
                }

                values.at(i).at(j) = running_sum;
            }
        }
        Matrix *resault = new Matrix(values, (int)this->rows, (int)mat.columns);
        return *resault;
    }

    Matrix &Matrix::operator+=(const Matrix &mat)
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        *this = *this + mat;
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &mat)
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        *this = *this - mat;
        return *this;
    }

    Matrix &Matrix::operator*=(const Matrix &mat)
    {
        if (this->columns != mat.rows)
        {
            throw "Multiplication Not Defined For These Dimension";
        }

        *this = *this * mat;
        return *this;
    }

    Matrix &Matrix::operator*(const double &scalar)
    {
        const vector<vector<double>> &temp_vect = this->matrix;
        size_t row = this->rows;
        size_t col = this->columns;

        vector<vector<double>> end_vect(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                end_vect.at(i).at(j) = temp_vect.at(i).at(j) * scalar;
            }
        }
        Matrix *resault = new Matrix(end_vect, (int)row, (int)col);
        return *resault;
    }

    Matrix &Matrix::operator*=(const double &scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    bool &Matrix::operator<(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        return flag;
    }

    bool &Matrix::operator<=(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return flag;
    }

    bool &Matrix::operator>(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return flag;
    }

    bool &Matrix::operator>=(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return flag;
    }

    bool &Matrix::operator==(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return flag;
    }

    bool &Matrix::operator!=(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return flag;
    }

    Matrix &Matrix::operator+()
    {
        Matrix *resault = new Matrix(*this);
        return *resault;
    }

    Matrix &Matrix::operator-()
    {
        Matrix *resault = new Matrix((*this) * -1);
        return *resault;
    }

    Matrix &Matrix::operator++(int num)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->matrix.at(i).at(j)++;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->matrix.at(i).at(j)++;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator--(int num)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->matrix.at(i).at(j)--;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                this->matrix.at(i).at(j)--;
            }
        }
        return *this;
    }
}
