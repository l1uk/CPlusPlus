//
// Created by Luca on 16/05/2023.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int lambdaFunc() {

    // <type> <name> =
    // [<capture list>] (variables from current scope)
    // (<function args>)
    // -> <return type> {<function body>}

    auto func = [](int i) -> int { return i * 2; };

    int x = func(2);

    // auto is used because the compiler generates specific types for each lambda

    size_t v1 = 42;

    // the parameter is copied from local scope and cannot be modified
    auto f = [v1] { return v1; };

    v1 = 0;
    auto j = f();

    cout << j << endl;


    v1 = 42;
    // the parameter is passed as reference
    auto f1 = [&v1] { return v1; };

    v1 = 0;
    auto j1 = f1();

    cout << j1 << endl;


    v1 = 42;

    // the parameter is copied from local scope and can be modified
    auto f2 = [v1]()mutable { return ++v1; };

    v1 = 0;
    auto j2 = f2();

    cout << j2 << endl;


    v1 = 42;
    // the parameter is passed as reference and incremented
    auto f3 = [&v1] { return ++v1; };

    v1 = 0;
    auto j3 = f3();

    cout << j3 << endl;

    v1 = 42;
    size_t *const p = &v1;
    // the parameter is passed as a pointer
    auto f4 = [p] { return ++*p; };
    auto j4 = f4();

    cout << j4 << endl;

    v1 = 0;
    j4 = f4();

    cout << j4 << endl;

    vector<string> vect;

    string next_word;
    while (cin >> next_word) {
        if (next_word == "exit") { break; }
        vect.push_back(next_word);
    }
    cin.clear();

    for_each(vect.begin(), vect.end(), [](const string &s) -> void {
        cout << s << "      ";
    });
    cout << endl;
    sort(vect.begin(), vect.end(), [](const string &s1, const string &s2) -> bool {
        return s1 < s2;
    });

    cout << endl;

    return 0;
}

