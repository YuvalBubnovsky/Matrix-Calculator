#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

namespace zich
{
    class Matrix
    {
    private:
        int rows;
        int columns;
        vector<vector<double>> matrix;

    public:

        // Constructors
        Matrix(vector<double> matVector, int rows, int columns);
        Matrix(int rows, int columns);

        // Destructor
        ~Matrix();
    };
};