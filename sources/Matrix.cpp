#include "Matrix.hpp"

using std::istream;
using std::ostream;
using std::string;

namespace zich
{
    bool flag = true;

    /*  
        Function to overload output (<<) operator, the function recieves a matrix
        and builds a string from it, where each block encapsuled by [] is a row in
        the matrix
    */
    ostream &operator<<(ostream &out, const Matrix &mat) // Credit to Yonatan Ratner for helping with this function
    {
        string mat_string;
        string temp;
        string sub_string;
        size_t index = 0;
        for (size_t i = 0; i < mat.rows; i++)
        {
            temp = "[";
            for (size_t j = 0; j < mat.columns; j++)
            {
                if (j != 0 && j < mat.columns)
                {
                    temp += " ";
                }
                sub_string = std::to_string(mat.matrix.at(i).at(j));
                index = sub_string.find('.', 0);
                sub_string = sub_string.substr(0, index);
                temp += sub_string;
            }
            temp += "]";
            if (i < mat.rows - 1)
            {
                temp += "\n";
            }
            mat_string += temp;
        }
        out << mat_string;
        return out;
    }

    istream &operator>>(istream &in, Matrix &mat) // Credit to Amir Sabag for helping with this function
    {
        string input;
        getline(in, input);
        size_t pos = 0;
        vector<string> tokens;

        // First, we split the string on ", " to get the rows
        while ((pos = input.find(", ")) != string::npos)
        {
            tokens.push_back(input.substr(0, pos));
            input.erase(0, pos + 2);
        }
        tokens.push_back(input.substr(0, input.size()));

        size_t row = tokens.size(); // this is the number of rows the matrix has
        if (row == 0) // we will be dividing by this later, so need to make sure it's not 0
        {
            throw "Invalid Input!";
        }
        vector<double> vect; // This will go into the returned matrix
        for (size_t i = 0; i < row; i++)
        {
            // This removes the [] at the start and end of each row-string
            tokens.at(i).erase(0, 1);
            tokens.at(i).erase(tokens.at(i).size() - 1, 1);
            tokens.at(i).append(" ");
        }

        // Next, this loop works on the string again, converting all numbers to doubles using stod
        for (size_t i = 0; i < row; i++)
        {
            while ((pos = tokens.at(i).find(' ')) != string::npos)
            {
                vect.push_back(stod(tokens.at(i).substr(0, pos)));
                tokens.at(i).erase(0, pos + 1);
            }
        }

        // number of columns is total matrix size divided by rows (we made sure rows != 0)
        size_t col = (vect.size()) / row;
        
        mat = Matrix(vect, row, col);
        return in;
    }

    Matrix operator*(double scalar, const Matrix &mat)
    {
        // we define a temp matrix which will be multiplied by the scalar
        vector<vector<double>> temp_vect = mat.matrix;
        vector<vector<double>> end_vect(mat.rows, vector<double>(mat.columns, 0));

        for (size_t i = 0; i < mat.rows; i++)
        {
            for (size_t j = 0; j < mat.columns; j++)
            {
                // iterating over the matrices and applying each multiplication to each cell
                end_vect.at(i).at(j) = temp_vect.at(i).at(j) * scalar;
            }
        }
        return Matrix(end_vect, mat.rows, mat.columns);
    }

    // Helper function to check if matrix dimension are equal - needed for some operators
    bool Matrix::dim_check(const Matrix &mat) const
    {
        bool status = false;
        if (rows == mat.rows && columns == mat.columns)
        {
            return !status;
        }
        return status;
    }

    // Helper function to calculate sum of a matrix
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
            // division and modulo manipulation to avoid doing nested loops
            matr.at(i / static_cast<size_t>(columns)).at(i % static_cast<size_t>(columns)) = mat.at(i);

            this->matrix = matr;
            this->rows = static_cast<size_t>(rows);
            this->columns = static_cast<size_t>(columns);
        }
    }

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
    {
        this->matrix = mat.matrix;
        this->rows = mat.rows;
        this->columns = mat.columns;
    }

    // Destructor
    Matrix::~Matrix()
    {
        for (size_t i = 0; i < this->rows; i++)
        {
            this->matrix.at(i).clear();
        }
        this->matrix.clear();
    }

    Matrix Matrix::operator+(const Matrix &mat) const // Adding two matrices
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }

        vector<vector<double>> vector1 = mat.matrix;
        vector<vector<double>> vector2 = this->matrix;

        vector<vector<double>> values(rows, vector<double>(columns, 0));
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                values.at(i).at(j) = vector1.at(i).at(j) + vector2.at(i).at(j);
            }
        }
        return Matrix(values, rows, columns);
    }

    Matrix Matrix::operator-(const Matrix &mat) const // Substracting two matrices
    {
        if (!dim_check(mat))
        {
            throw "Matrix Dimensions Do No Match!";
        }
        vector<vector<double>> vector1 = mat.matrix;
        vector<vector<double>> vector2 = this->matrix;

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

    Matrix Matrix::operator*(const Matrix &mat) const // Multiplying two matrices
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

    Matrix Matrix::operator+=(const Matrix &mat) // Adding a matrix to a matrix
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }

        *this = *this + mat;
        return *this;
    }

    Matrix Matrix::operator-=(const Matrix &mat) // Substracting a matrix from a matrix
    {
        if (!dim_check(mat))
        {
            throw "Invalid Dimensions!";
        }
        *this = *this - mat;
        return *this;
    }

    Matrix Matrix::operator*=(const Matrix &mat) // Multiplying
    {
        if (this->columns != mat.rows)
        {
            throw "Multiplication Not Defined For These Dimension";
        }

        *this = *this * mat;
        return *this;
    }

    Matrix Matrix::operator*(const double &scalar) // Multiplying a matrix by a scalar
    {
        vector<vector<double>> temp_vect = this->matrix;

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
        // Using logic rules, this is just the opposite of >
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
        // Using logic rules, this is just the opposite of <
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
        // just the opposite of ==
        return !((*this) == mat);
    }

    Matrix Matrix::operator+() // Unary +
    {
        return Matrix(*this);
    }

    Matrix Matrix::operator-() // Unary -
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
