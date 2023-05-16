#include <iostream>
#include <vector>
#include <initializer_list>
#include <iterator>

using namespace std;

template<class T>
struct S {
    std::vector<T> v;

    S(std::initializer_list<T> l) : v(l) {
        std::cout << "constructed with a " << l.size() << "-element list\n";
    }

    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }

    std::pair<const T *, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // copy list-initialization in return statement
        // this is NOT a use of std::initializer_list
    }
};


struct X {
    X(int i) { cout << "X(int i)" << endl; }

    explicit X(X &) { cout << "X(X&)" << endl; } // to avoid implicit constructor calls in this scenario X x4 = x2;

    X(initializer_list<int>) { cout << "X(initializer_list<int>)" << endl; }

    X &operator=(X &) {
        cout << "X& operator=(X&)" << endl;
        return *this;
    }

};

template<typename T>
std::vector<T> make_vector(T a) {
    return std::vector<T>(a);
}

int uniformInitialization() {


    X x1(1);
    X x2{12, 33, 44};

    X x3(x1);
    //X x4 = x2; // does not work
    X x4(11);
    x4 = x2; // no implicit call

    S<int> s = {1, 2, 3, 4, 5}; // copy list-initialization
    s.append({6, 7, 8});

    cout << "Vector size: " << s.c_arr().second << endl;

    copy(
            s.v.begin(), s.v.end(), ostream_iterator<int>(cout, " ") // elegant way of printing vector
    );
    cout << endl;
    auto list = {1, 2, 3, 4, 5};

    cout << "Auto list has size: " << list.size() << endl;

    for (auto x: list) {
        cout << x << endl;
    }
    std::vector<int> s1 = {1, 2, 3, 4};
    std::vector<int> r{1, 2, 3, 4};
    std::vector<int> p({1, 2, 3, 4});
    std::vector<int> t;
    t.insert(t.begin(), {1, 2, 3, 4});
    auto test = {1, 2, 3, 4};
    std::vector<int> er(test);
    cout << endl;
    auto v = make_vector(1);
    for (auto i: v) {
        std::cout << i << std::endl;
    }

    auto *sos = new int();
    cout << *sos << endl;

    return 0;

}