#include <iostream>
#include <vector>

using namespace std;

template<class T, class U>
auto add(T t, U u) {
    return t + u;
}

int lambda() {

    auto lambda = [](int x) { return x + 2; };

    cout << lambda(2) << endl;

    cout << "Lambda has type: " << typeid(lambda).name() << endl;

    auto res = add(2, 3.0);

    cout << res << " has type " << typeid(res).name() << endl;

    auto a = 1;
    auto &i = a;
    cout << i << endl;
    return 0;
}