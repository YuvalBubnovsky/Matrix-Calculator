#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace zich;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
    cout<< "please input ur first matrix via format uwu\n'[num1 ... num_col], [num1 ... num_col], ..... [num1 ... num_col]'" << endl;
    Matrix mat1(5,5);
    cin >> mat1;
    
    Matrix mat2(5,5);
    cout << "please input the second matrix via the same format above uwu \n";
    cin >> mat2;

    vector<double> mat = {1};
    Matrix mat3({1}, 1, 1); // default till will be setted as something
    std::cout << "mat3 default is:\n" << mat3 << std::endl<< std::endl;;

    char flag = '\0';
    std::cout << "to sum mat2 into mat1 press a\nto sum mat2 and mat1 to mat3 press b\nsame with sub for c, d\nsame with mul for e, f\nto check mat1==mat2 press g\nto check mat1 < mat2 press h\nto check mat1 <= mat2 press i\nto print mat1 endl, mat2 endl, mat3 endl press j\nanything else to exit\n" << std::endl;
    for (;;)
    {
        std::cin >> flag;
        std::cout << std::endl;
        if (flag == 'a')
        {
            mat3 = mat1+mat2;
            std::cout << "mat1+mat2 = mat3: " << std::endl << mat3 << std::endl<< std::endl;
        }
        else if (flag == 'b')
        {
            mat1+=mat2;
            std::cout << "mat1+=mat2 -> mat1:\n"<< mat1 << std::endl<< std::endl;
        }
        else if (flag == 'c')
        {
            mat3 = mat1-mat2;
            std::cout << "mat1-mat2 = mat3: " << std::endl << mat3 << std::endl<< std::endl;
        }
        else if (flag == 'd')
        {
            mat1-=mat2;
            std::cout << "mat1-=mat2 -> mat1:\n"<< mat1 << std::endl<< std::endl;
        }
        else if (flag == 'e')
        {
            mat3 = mat1*mat2;
            std::cout << "mat1*mat2 = mat3: " << std::endl << mat3 << std::endl<< std::endl;
        }
        else if (flag == 'f')
        {
            mat1*=mat2;
            std::cout << "mat1*=mat2 -> mat1:\n"<< mat1 << std::endl<< std::endl;
        }
        else if (flag == 'g')
        {
            std::cout << "mat1 == mat2: " << (mat1 == mat2) << std::endl<< std::endl;
        }
        else if (flag == 'h')
        {
            std::cout << "mat1 < mat2: " << (mat1 < mat2) << std::endl<< std::endl;
        }
        else if (flag == 'i')
        {
            std::cout << "mat1 <= mat2: " << (mat1 <= mat2) << std::endl<< std::endl;
        }
        else if (flag == 'j')
        {
            std::cout << mat1 << std::endl<< std::endl << mat2 << std::endl<< std::endl << mat3 << std::endl<< std::endl;       
        }
        else
        {
            break;
        }
    }
    std::cout<< "dank ya uwu\ncya next time <3\n";
    return 1;
}