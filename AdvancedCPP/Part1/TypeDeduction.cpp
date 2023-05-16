#include <type_traits>
#include <vector>
#include <iostream>


int typeDeduction() {

    auto i = 0; // deduct type

    static_assert(std::is_same<decltype(i), int>::value, "Type not okay"); // check if type if correct

    std::vector<int> vec{1, 2, 3};

    for (auto it = vec.begin(); it != vec.end(); it++) {
        static_assert(std::is_same<std::vector<int>::iterator, decltype(it)>::value, "Type not okay");
        std::cout << *it << std::endl;
    }

    return 0;
}