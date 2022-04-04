#include "Matrix.hpp"
#include "doctest.h"
#include <array>
#include <string>

using namespace zich;

TEST_CASE("Constructor Test")
{

    // check for ints
    vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> vec2 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    CHECK_NOTHROW(Matrix a(vec, 3, 3));
    CHECK_NOTHROW(Matrix b(vec2, 6, 6));

    // check for double
    vec = {1.5, 0, 0, 0, 1.5, 0, 0, 0, 1.5};
    vec2 = {2.6, 2.7, 2.2, 2.8, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1, 2.1};

    CHECK_NOTHROW(Matrix a(vec, 3, 3));
    CHECK_NOTHROW(Matrix b(vec2, 6, 6));

    // small matrix
    vec = {1, 1, 1};
    CHECK_NOTHROW(Matrix a(vec, 1, 3));
    vec2 = {2.2, 3.5, 8.9};
    CHECK_NOTHROW(Matrix b(vec, 1, 3));

    // matrix with 0 rows or columns
    CHECK_THROWS(Matrix a(vec, 0, 3));
    CHECK_THROWS(Matrix a(vec, 3, 0));
}

TEST_CASE("Good Input")
{
    SUBCASE("Global Operators")
    {
    }

    SUBCASE("Comparison Operators")
    {
        vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> vec2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
        Matrix mat1(vec, 3, 3);
        Matrix mat2(vec, 3, 3);
        Matrix mat3(vec, 3, 3);
        CHECK(mat1 == mat2);
        CHECK(mat1 >= mat2);
        CHECK(mat1 <= mat2);
        CHECK(mat3 > mat1);
        CHECK(mat3 > mat2);
        CHECK(mat2 < mat3);
        CHECK(mat1 < mat3);
        CHECK(mat1 != mat3);
        CHECK(mat2 != mat3);
        CHECK(mat3 != mat2);
        CHECK(mat3 != mat1);
    }

    SUBCASE("Single Matrix Operators")
    {
        vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> vec2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
        vector<double> vec3 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        Matrix mat1(vec, 3, 3);
        Matrix mat2(vec2, 3, 3);
        Matrix mat3(vec, 3, 3);
        Matrix mat4(vec3, 3, 3);
        vector<double> res1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> res2 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> res3 = {9, 0, 0, 0, 9, 0, 0, 0, 9};
        Matrix res_mat1(res1, 3, 3);
        Matrix res_mat2(res2, 3, 3);
        CHECK(mat4 == mat1);
        ++mat4;
        CHECK(mat4 == mat2);
        --mat4;
        CHECK(mat4 == mat1);
    }

    SUBCASE("Double Matrix Operators")
    {
        vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> vec2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
        vector<double> vec3 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        Matrix mat1(vec, 3, 3);
        Matrix mat2(vec2, 3, 3);
        Matrix mat3(vec, 3, 3);
        Matrix mat4(vec3, 3, 3);
        vector<double> res1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> res2 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        Matrix res_mat1(res1, 3, 3);
        Matrix res_mat2(res2, 3, 3);
        CHECK((mat1 * mat2) == mat2);
    }
}

TEST_CASE("Bad Input")
{
    SUBCASE("Constructors")
    {
        vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};

        // 0 rows/columns
        CHECK_THROWS(Matrix a(vec, 0, 1));
        CHECK_THROWS(Matrix a(vec, 1, 0));

        // Not enough arguments to build matrix
        vec = {1.5, 0, 0};
        CHECK_THROWS(Matrix a(vec, 3, 3));
    }

    SUBCASE("Invalida Dimensions")
    {
        vector<double> vec = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        vector<double> vec2 = {1, 1, 1, 1, 1, 1};
        Matrix a(vec,3,3);
        Matrix b(vec2,3,2);
        CHECK_THROWS(a+b);
        CHECK_THROWS(a-b);
        CHECK_THROWS(a*b);
    }
}
