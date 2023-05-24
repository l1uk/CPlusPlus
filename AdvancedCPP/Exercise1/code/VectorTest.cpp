// TODO test begin && end && size
// IN vector.h change () operator to [] operator

#include "Vector.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using std::size_t;

class TestCase {
public:
    explicit TestCase(std::string name) : name_(name) {
        std::cout << "Test Case START:\t" << name_ << std::endl;
    }

    ~TestCase() { std::cout << "Test Case END:  \t" << name_ << std::endl; }

private:
    std::string name_;
};

#define TESTCASE(name) TestCase _testcase(name)

bool almostEqual(double a, double b, double epsilon = 1e-13) {
    return std::abs(a - b) <= epsilon;
}

// this function allows only vectors of equal dimensions
bool almostEqual(const Vector &a, const Vector &b, double epsilon = 1e-13) {
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        if (!almostEqual(a[i], b[i], epsilon)) {
            return false;
        }
    }
    return true;
}

void test_get_set(size_t rows = 2, double initValue = 1.0) {
    TESTCASE("test_get_set");
    const Vector v1(rows, initValue);
    for (size_t i = 0; i < rows; ++i) {
        assert("const get check" && v1[i] == initValue);
    }
    // compile time check: taking address of const reference
    assert(*&v1[0] == v1[0]);

    auto begin = &v1[0];
    auto end = &v1[rows];
    size_t diff = end - begin;
    assert("memory layout check" && (diff == rows));
    assert("row wise order check" && (&v1[1] - &v1[0] == 1));
}

void test_memory(size_t rows = 2, double initValue = 1.0) {
    TESTCASE("test_memory");
    {
        Vector v1(rows, initValue);
        assert("copy ctr check" && almostEqual(Vector(v1), v1, 0.0));
        assert("no alias check" && &Vector(v1)[0] != &v1[0]);
        Vector v2(rows, initValue);
        v2 = v1;
        assert("assignment check" && almostEqual(v1, v2, 0.0));
        assert("no alias check" && &v1[0] != &v2[0]);
        // allow zero dimensions
        Vector v3(0, 0.0);
        // allow assignment of vectors of different dimensions
        v3 = Vector(1, 0.0);
        v3 = v1;
        assert("check assignment" && almostEqual(v1, v3, 0.0));
        auto initValue2 = 1.5;
        Vector v4(rows, initValue2);
        Vector v4copy(rows, initValue2);
        v4 = v4;
        // check self assignment
        assert("self assignment check" && almostEqual(v4, v4copy, 0.0));
    }
    // important: if your code does not support move constructor / move assignment
    // the following will work anyway uses move constructor if present else: uses
    // copy ctor
    {
        // TODO check for move constructor assignment
        Vector v1(rows, initValue);
        Vector move_constructed(std::move(Vector(v1)));
        assert("testing copy/move constructor" &&
               almostEqual(v1, move_constructed, 0.0));
    }
    // uses move assignment if present else: uses assignment operator
    {
        Vector v1(rows, initValue);
        Vector v2(1, 0);
        v2 = std::move(Vector(v1));
        assert("testing assignment/move assignment" && almostEqual(v1, v2, 0.0));
    }
}

void test_compare(size_t rows = 2, double v = 1.0) {
    TESTCASE("test_compare");
    {
        Vector v1(rows, v);
        assert("compare check" && v1 == v1);
        assert("compare check" && !(v1 != v1));
        assert("compare check" && v1 == Vector(v1));
        assert("compare check" && !(v1 != Vector(v1)));
        const Vector v2 = v1;
        v1[rows - 1] += 1;
        assert("compare check" && v1 != v2);
        assert("compare check" && !(v1 == v2));
    }
    assert("compare check" && Vector(rows, v) == Vector(rows, v));
    assert("compare check" && !(Vector(rows, v) != Vector(rows, v)));
    // allow comparison of matrices of different dimensions
    assert("compare check" && Vector(rows, v) != Vector(rows + 1, v));
    assert("compare check" && !(Vector(rows, v) == Vector(rows - 1, v)));
    assert("compare check" && Vector(0, 0) != Vector(rows, v));
    assert("compare check" && !(Vector(0, 0) == Vector(rows, v)));
    assert("compare check" && Vector(0, 0) == Vector(0, 0));
    assert("compare check" && !(Vector(0, 0) != Vector(0, 0)));
}

void test_arithmetic(size_t rows = 4) {
    TESTCASE("test_arithmetic");
    Vector v1(rows, 0);
    Vector v2(rows, 0);
    Vector sum_result(rows, 0);
    Vector diff_result(rows, 0);
    for (size_t i = 0; i < rows; ++i) {
        v1[i] = i;
        v2[i] = 2 * i;
        sum_result[i] = v1[i] + v2[i];
        diff_result[i] = v1[i] - v2[i];
    }
    Vector sum1 = v1 + v2;
    Vector sum2 = v1;
    sum2 += v2;
    Vector diff1 = v1 - v2;
    Vector diff2 = v1;
    diff2 -= v2;

    assert("check operator+" && almostEqual(sum_result, sum1));
    assert("check operator+=" && almostEqual(sum_result, sum2));
    assert("check operator-" && almostEqual(diff_result, diff1));
    assert("check operator-=" && almostEqual(diff_result, diff2));

    double a = 3, b = 4;
    Vector prod = Vector(1, a) * Vector(1, b);
    assert("check operator*" && almostEqual(prod, Vector(1, a * b)));
    prod = Vector(rows, a) * Vector(rows, b);
    assert("check operator*" && almostEqual(prod, Vector(rows, a * b)));
    Vector one(rows, 0);
    Vector v(rows, 0);
    for (size_t i = 0; i < rows; ++i) {
        one[i] = 1;
        v[i] = i;
    }
    assert("check operator*" && almostEqual(v, one * v));
}

void test_input_output_self_consistency(size_t rows = 4) {
    TESTCASE("test_input_output_self_consistency");
    Vector v1(rows, 0);
    Vector v2(rows, 0);
    for (size_t i = 0; i < rows; ++i) {
        v1[i] = i / 9.0;
    }
    std::stringstream ss;
    ss << v1;
    ss >> v2;
    // checking if your operator>> can parse your own output generated by
    // operator<<
    assert("check output and input operator" && almostEqual(v1, v2, 1e-4));
}

void test_initalizer_list() {
    std::initializer_list<double> l = {0, 1, 2, 3, 4};
    Vector v1(l);
    Vector v2 = l;
    for (size_t i = 0; i < v2.size(); ++i) {
        assert("check initializer list" && almostEqual(v1[i], i));
        assert("check initializer list" && almostEqual(v2[i], i));
    }
}

void test_size_iter() {
    TESTCASE("test_size");
    size_t n = 5;
    const Vector v1(n, 0.0);
    assert("check size" && n == v1.size());
    assert("check size" && signed(n) == (v1.end() - v1.begin()));

    size_t i = 0;
    for (auto it = v1.begin(); it != v1.end(); it++) {
        i++;
    }
    assert("check size" && n == i);

    const Vector v2{1.0};
    assert("check size" && v2.size() == 1U);
}

void test_dot_product_and_norm() {
    TESTCASE("test_dot_product_and_norm");
    assert("check dot product" && almostEqual(Vector({1}).dot(Vector{1}), 1));
    assert("check dot product" &&
           almostEqual(Vector({1, 0}).dot(Vector{0, 1}), 0));

    const Vector v1({1, 3, -5});
    const Vector v2({4, -2, -1});
    assert("check dot product" && almostEqual(v1.dot(v2), 3));

    const Vector v3({1.3333});
    assert("check return value of std::accumulate" &&
           almostEqual(v3.dot(Vector{1}), v3[0]));
}

void test_swap() {
    TESTCASE("test_swap");
    const Vector a(5, 3.5);
    const Vector b(1, 1);
    Vector copy_a(a);
    Vector copy_b(b);
    swap(copy_a, copy_b);
    assert("check swap" && almostEqual(a, copy_b, 0.0) &&
           almostEqual(b, copy_a, 0.0));
}

int main() {
    test_get_set();
    test_memory();
    test_compare();
    test_arithmetic();
    test_input_output_self_consistency();
    test_initalizer_list();
    test_dot_product_and_norm();
    test_size_iter();
    test_swap();
    std::cout << "all tests finished without assertion errors" << std::endl
              << "GOOD JOB! Check memory leakage now!" << std::endl;
}
