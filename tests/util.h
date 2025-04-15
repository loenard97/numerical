#ifndef NUMERICAL_TESTS_UTILH
#define NUMERICAL_TESTS_UTILH

#include "../numerical.h"

const char* NUMERICAL_TEST_INFO_STR = "\033[1;32m[INFO]\033[0m";
const char* NUMERICAL_TEST_WARN_STR = "\033[1;33m[WARN]\033[0m";
const char* NUMERICAL_TEST_ERRO_STR = "\033[1;31m[ERRO]\033[0m";

#define ASSERT_NEAR_EQUAL(a, b, tol) assert_near_equal(a, b, tol, __FILE__, __LINE__)

template <typename T>
int assert_near_equal(T a, T b, T tolerance, const char* file, int line) {
    if (NUMERICAL_UTIL_ABS(b - a) > tolerance) {
        printf("%s %s:%d assert near equal failed: %f != %f\n", NUMERICAL_TEST_ERRO_STR, file, line, a, b);
        return 1;
    }
    printf("%s %s:%d assert near equal succeeded: %f == %f\n", NUMERICAL_TEST_INFO_STR, file, line, a, b);
    return 0;
}

#endif