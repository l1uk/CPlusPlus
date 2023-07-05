#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <functional>
#include <cmath>

#include "Vector.h"


// TODO how to check that move constructor/assignments moves data?
// TODO test with elements which need to be freed
// TODO check for free in move assignment/constructor

using namespace std;

class TestCase {
public:
    explicit TestCase(string name) :
            name_(std::move(name)) {
        std::cout << "Test Case START:\t" << name_ << std::endl;
    }

    ~TestCase() {
        std::cout << "Test Case END:  \t" << name_ << std::endl;
    }

private:
    std::string name_;
};

#define TESTCASE(name) TestCase _testcase(name)

template<typename T>
bool equal(const Vector<T> &a, const Vector<T> &b) {
    if (a.size() != b.size())
        return false;


    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i])
            return false;


    }
    return true;
}

template<typename T>
void print(const Vector<T> &v) {
    for (auto it: v)
        cout << it << " ";
    cout << endl;
}

void test_get_set(int initValue = 1) {
    TESTCASE("test_get_set");
    Vector<int> v1;
    v1 = {1, 1, 1, 1};
    for (int i: v1) {
        assert("const get check" && i == initValue);
    }
    // compile time check: taking address of const reference
    assert(*&v1[0] == v1[0]);

    auto begin = &v1[0];
    auto end = &v1[v1.size()];
    size_t diff = end - begin;
    assert("memory layout check" && (diff == v1.size()));
    assert("row wise order check" && (&v1[1] - &v1[0] == 1));
    assert("equal to itself check" && (equal(v1, v1)));
}

void test_capacity(int initValue = 1) {
    TESTCASE("test_capacity");
    Vector<int> v1;
    assert("size check" && v1.size() == 0);
    assert("capacity check" && v1.capacity() == 0);
    v1.push_back(initValue);
    assert("size check" && v1.size() == 1);
    assert("capacity check" && v1.capacity() == 2);
    v1.push_back(1);
    assert("size check" && v1.size() == 2);
    assert("capacity check" && v1.capacity() == 2);
    v1.push_back(1);
    assert("size check" && v1.size() == 3);
    assert("capacity check" && v1.capacity() == 4);
    v1.push_back(initValue);
    assert("size check" && v1.size() == 4);
    assert("capacity check" && v1.capacity() == 4);
    v1.push_back(initValue);
    assert("size check" && v1.size() == 5);
    assert("capacity check" && v1.capacity() == 8);
}


void test_memory(size_t elements = 8, const string &initValue = "hi") {
    TESTCASE("test_memory");
    {
        Vector<string> v1;
        for (size_t i = 0; i < elements; ++i) {
            v1.push_back(initValue);
        }
        assert("copy ctr check" && equal(Vector<string>(v1), v1));
        assert("no alias check" && &Vector<string>(v1)[0] != &v1[0]);
        Vector<string> v2;
        v2 = v1;
        assert("assignment check" && equal(v1, v2));
        assert("no alias check" && &v1[0] != &v2[0]);
        Vector<string> v4;
        for (size_t i = 0; i < elements; ++i) {
            v4.push_back(initValue);
        }
        Vector<string> v4copy;
        for (size_t i = 0; i < elements; ++i) {
            v4copy.push_back(initValue);
        }
        v4 = v4;
        // check self assignment
        assert("self assignment check" && equal(v4, v4copy));
    }
    // important: if your code does not support move constructor / move assignment the following will work anyway
    // uses move constructor if present else: uses copy ctor
    {
        Vector<string> v1;
        for (size_t i = 0; i < elements; ++i) {
            v1.push_back(initValue);
        }
        Vector<string> move_constructed(move(Vector<string>(v1)));
        assert("testing copy/move constructor" && equal(v1, move_constructed));
    }
    // uses move assignment if present else: uses assignment operator
    {
        Vector<string> v1;
        for (size_t i = 0; i < elements; ++i) {
            v1.push_back(initValue);
        }
        Vector<string> v2;
        v2 = move(Vector<string>(v1));
        assert("testing assignment/move assignment" && equal(v1, v2));
    }
}


int main() {
    test_get_set();
    test_capacity();
    test_memory();
    std::cout << "all tests finished without assertion errors" << std::endl << "GOOD JOB! Check memory leakage now!"
              << std::endl;
}


