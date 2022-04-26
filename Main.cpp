#include "Matrix.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::string;

using namespace zich;

int main()
{

    Matrix mat_1;
    Matrix mat_2;
    char input;
    double scalar;

    //  Creating two matrices to work on them
    while (mat_1.getRows() == 0 || mat_2.getRows() == 0)
    {
        cout << "Enter M for matrix input or R for random 3x3 matrix or I for I_3" << endl;
        cin >> input;
        if (input == 'M')
        {
            cout << "Enter the first matrix" << endl;
            try
            {
                cin >> mat_1;
            }
            catch (exception &e)
            {
                cin >> mat_1;
            }
        }
        else if (input == 'R')
        {
            for (int i = 0; i < 9; i++)
            {
                mat_1 = Matrix({(double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10),
                                (double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10),
                                (double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10)},
                               3, 3);
            }
        }
        else if (input == 'I')
        {
            mat_1 = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3);
        }
        cout << "Enter M for matrix input or R for random 3x3 matrix or I for I_3" << endl;
        cin >> input;
        if (input == 'M')
        {
            cout << "Enter the second matrix" << endl;
            try
            {
                cin >> mat_2;
            }
            catch (exception &e)
            {
                cin >> mat_2;
            }
        }
        else if (input == 'R')
        {
            for (int i = 0; i < 9; i++)
            {
                mat_2 = Matrix({(double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10),
                                (double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10),
                                (double)(rand() % 10), (double)(rand() % 10), (double)(rand() % 10)},
                               3, 3);
            }
        }
        else if (input == 'I')
        {
            mat_2 = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3);
        }
    }
    // Few matrix operators for the interactive presentation
    cout << "Matrix A:\n"
         << mat_1 << endl;
    cout << "\n";
    cout << "Matrix B:\n"
         << mat_2 << endl;
    cout << "\n";

    cout << "Enter a scalar to multiply A by" << endl;
    cin >> scalar;
    cout << scalar << "*mat_1:\n"
         << mat_1 * scalar << endl;
    cout << "\n";

    cout << "Multiplying B from the other side.." << endl;
    cout << "mat_2"
         << "*"
         << ":\n"
         << scalar * mat_2 << endl;
    cout << "\n";

    cout << "mat_1*mat_2:\n"
         << mat_1 * mat_2 << endl;
    cout << "\n";

    cout << "mat_1+mat_2:\n"
         << mat_1 + mat_2 << endl;
    cout << "\n";

    cout << "mat_1-mat_2:\n"
         << mat_1 - mat_2 << endl;
    cout << "\n";

    cout << "mat_1==mat_2\n"
         << (mat_1 == mat_2) << endl;
    cout << "\n";

    cout << "mat_1!=mat_2\n"
         << (mat_1 != mat_2) << endl;
    cout << "\n";

    cout << "mat_1<=mat_2\n"
         << (mat_1 <= mat_2) << endl;
    cout << "\n";

    cout << "mat_1>=mat_2\n"
         << (mat_1 >= mat_2) << endl;
    cout << "\n";

    cout << "mat_1<mat_2\n"
         << (mat_1 < mat_2) << endl;
    cout << "\n";

    cout << "mat_1>mat_2\n"
         << (mat_1 > mat_2) << endl;
}