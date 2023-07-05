#pragma once

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <utility>

template<typename T>
class Vector {
public:
    Vector() = default;

    Vector(const Vector &);

    Vector &operator=(const Vector &);

    Vector(Vector &&) noexcept;

    Vector &operator=(Vector &&) noexcept;

    Vector &operator=(std::initializer_list<T>);

    ~Vector() noexcept;

    // add elements
    void push_back(const T &);

    void push_back(T &&);

    size_t size() const { return first_free - elements; }

    size_t capacity() const { return cap - elements; }

    T &operator[](size_t n) { return elements[n]; }

    const T &operator[](size_t n) const { return elements[n]; }

    T *begin() const { return elements; }

    T *end() const { return first_free; }

// pointer to first element in the array

private:
    T *elements = nullptr;
    static std::allocator<T> alloc; // allocates the elements
    // used by functions that add elements to the Vector
    void chk_n_alloc() { if (first_free == cap) reallocate(); }

    // utilities used by copy constructor, assignment operator, and destructor
    std::pair<T *, T *>
    alloc_n_copy(const T *, const T *);

    // free all memory
    void free();

    // get more space and move existing elements
    void reallocate();

    // pointer to first free element in the array
    T *first_free = nullptr;
    // pointer to one past the end of the array
    T *cap = nullptr;
};

// include of the cpp file is here necessary because it is a templated class
#include "Vector.cpp"
