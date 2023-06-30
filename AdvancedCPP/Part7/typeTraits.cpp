#include <type_traits>

// Euclid's Algorithm
template<typename T>
T gcd(T a, T b) {

    // ensure that T is an integral type
    static_assert(std::is_integral<T>::value, "T should be an integral type!");

    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}