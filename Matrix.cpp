#include "Matrix.hpp"
#include <cmath>


namespace zich
{
    Matrix::Matrix(vector<double> matVector, int rows, int columns)
    {
        if (rows <= 0 || columns <= 0)
        {
            throw std::invalid_argument("Rows/Columns Must Be A Positive Number!");
        }
        if (matVector.size() != rows * columns)
        {
            throw std::invalid_argument("Not Enough Arguments!");
        }
        this->rows = rows;
        this->columns = columns;
        this->matrix.resize((unsigned int)rows);
        for (unsigned int i = 0; i < rows; i++)
        {
            this->matrix[i].resize((unsigned int)columns);
        }
        unsigned int index = 0;
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                this->matrix[i][j] = matVector[index];
                index++;
            }
        }
    }

    Matrix::Matrix(int rows, int columns){
        if (rows<=0 || columns<=0){
            throw std::invalid_argument("Rows/Columns Must Be A Positive Number!");
        }
        this->rows = rows;
        this->columns = columns;
        this->matrix.resize((unsigned int)rows);
        for (unsigned int i=0;i<rows;i++){
            this->matrix[i].resize((unsigned int)columns);
        }
    }

    Matrix::~Matrix(){
        for(unsigned int i=0;i<this->rows;i++){
            this->matrix[i].clear();
        }
        this->matrix.clear();
    }
}