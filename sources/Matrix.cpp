#include "Matrix.hpp"
#include <cmath>

using std::istream;
using std::move;
using std::ostream;
using std::string;

namespace zich
{
    bool flag = true;

    ostream &operator<<(ostream &out, const Matrix &mat)
    {
        const vector<vector<double>> &vect = mat.matrix;
        size_t rows = mat.rows;
        size_t columns = mat.columns;

        string ans;
        string temp;
        string sub_string;
        size_t index = 0;
        for (size_t i = 0; i < rows; i++)
        {
            temp = "[";
            for (size_t j = 0; j < columns; j++)
            {
                if (j != 0 && j < columns)
                {
                    temp += " ";
                }
                sub_string = std::to_string(mat.matrix.at(i).at(j));
                index = sub_string.find('.', 0);
                sub_string = sub_string.substr(0, index);
                temp += sub_string;
            }
            temp += "]";
            if (i < rows - 1)
            {
                temp += "\n";
            }
            ans += temp;
        }
        out << ans;
        return out;
    }

    istream &operator>>(istream &in, Matrix &mat)
    {
        string input_mat;
        getline(in, input_mat);
        string delimiter_2 = ", ";
        size_t pos = 0;
        vector<string> tokens;

        while ((pos = input_mat.find(delimiter_2)) != string::npos)
        {
            tokens.push_back(input_mat.substr(0, pos));
            input_mat.erase(0, pos + 2);
        }
        tokens.push_back(input_mat.substr(0, input_mat.size()));

        size_t row = tokens.size();
        vector<double> mat_vector;
        for (size_t i = 0; i < row; i++)
        {
            tokens.at(i).erase(0, 1);
            tokens.at(i).erase(tokens.at(i).size() - 1, 1);
            tokens.at(i).append(" ");
        }
        for (size_t i = 0; i < row; i++)
        {
            while ((pos = tokens.at(i).find(' ')) != string::npos)
            {
                mat_vector.push_back(stod(tokens.at(i).substr(0, pos)));
                tokens.at(i).erase(0, pos + 1);
            }
        }
        if (row == 0)
        {
            throw "Invalid Input!";
        }
        size_t col = (mat_vector.size()) / row;
        mat = Matrix(mat_vector, row, col);
        return in;
    }

    Matrix operator*(double scalar, const Matrix &mat)
    {
        const vector<vector<double>> &temp_vect = mat.matrix;
        size_t rows = mat.rows;
        size_t columns = mat.columns;

        vector<vector<double>> end_vect(rows, vector<double>(columns, 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                end_vect.at(i).at(j) = temp_vect.at(i).at(j) * scalar;
            }
        }
        return Matrix(end_vect, rows, columns);
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

    double Matrix::mat_sum(const Matrix &mat) const
    {
        double res = 0;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                res += mat.matrix.at(i).at(j);
            }
        }
        return res;
    }

    // If we get dimension in int, cast to size_t
    Matrix::Matrix(vector<double> mat, int rows, int columns)
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
    Matrix::Matrix(vector<vector<double>> mat, int rows, int columns)
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

    Matrix Matrix::operator+(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }

        const vector<vector<double>> &vector1 = mat.matrix;
        const vector<vector<double>> &vector2 = this->matrix;

        vector<vector<double>> values(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                values.at(i).at(j) = vector1.at(i).at(j) + vector2.at(i).at(j);
            }
        }
        return Matrix(values, rows, columns);
    }

    Matrix Matrix::operator-(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }
        const vector<vector<double>> &vector1 = mat.matrix;
        const vector<vector<double>> &vector2 = this->matrix;

        vector<vector<double>> values(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                values.at(i).at(j) = vector2.at(i).at(j) - vector1.at(i).at(j);
            }
        }
        return Matrix(values, rows, columns);
    }

    Matrix Matrix::operator*(const Matrix &mat) const
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
        return Matrix(values, this->rows, mat.columns);
    }

    Matrix Matrix::operator+=(const Matrix &mat)
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        *this = *this + mat;
        return *this;
    }

    Matrix Matrix::operator-=(const Matrix &mat)
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        *this = *this - mat;
        return *this;
    }

    Matrix Matrix::operator*=(const Matrix &mat)
    {
        if (this->columns != mat.rows)
        {
            throw "Multiplication Not Defined For These Dimension";
        }

        *this = *this * mat;
        return *this;
    }

    Matrix Matrix::operator*(const double &scalar)
    {
        const vector<vector<double>> &temp_vect = this->matrix;

        vector<vector<double>> end_vect(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns), 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                end_vect.at(i).at(j) = temp_vect.at(i).at(j) * scalar;
            }
        }
        return Matrix(end_vect, rows, columns);
    }

    Matrix Matrix::operator*=(const double &scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    bool Matrix::operator<(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        double res1 = mat_sum(*this);
        double res2 = mat_sum(mat);
        return (res1 - res2) < 0;
    }

    bool Matrix::operator<=(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return !((*this) > mat);
    }

    bool Matrix::operator>(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        double res1 = mat_sum(*this);
        double res2 = mat_sum(mat);
        return (res1 - res2) > 0;
    }

    bool Matrix::operator>=(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        return !((*this) < mat);
    }

    bool Matrix::operator==(const Matrix &mat) const
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        flag = true;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (this->matrix.at(i).at(j) != mat.matrix.at(i).at(j))
                {
                    flag = false;
                    return flag;
                }
            }
        }
        return flag;
    }

    bool Matrix::operator!=(const Matrix &mat) const
    {
        return !((*this) == mat);
    }

    Matrix Matrix::operator+()
    {
        return Matrix(*this);
    }

    Matrix Matrix::operator-()
    {
        return Matrix((*this) * -1);
    }

    Matrix Matrix::operator++(int num)
    {
        Matrix temp = *this;
        ++(*this);
        return temp;
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

    Matrix Matrix::operator--(int num)
    {
        Matrix temp = *this;
        --(*this);
        return temp;
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
