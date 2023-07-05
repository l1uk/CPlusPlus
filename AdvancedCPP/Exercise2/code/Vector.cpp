#include "Vector.h"

template<typename T> std::allocator<T> Vector<T>::alloc;

template<typename T>
inline
Vector<T>::~Vector() noexcept { free(); }

template<typename T>
inline
std::pair<T *, T *>
Vector<T>::alloc_n_copy(const T *b, const T *e) {
    auto data = alloc.allocate(e - b);

    return {data, std::uninitialized_copy(b, e, data)};
}

template<typename T>
inline
Vector<T>::Vector(Vector &&s) noexcept :
// take over resources from s
        elements(s.elements), first_free(s.first_free), cap(s.cap) { // move constructor
    // leave s in a state in which it is safe to run the destructor
    // Fixme
    //s.free();
    s.elements = s.cap = s.first_free = 0;

}

template<typename T>
inline
Vector<T>::Vector(const Vector &s) {
    // call copy to allocate exactly as many elements as in s
    // Fixme
    auto data = alloc_n_copy(s.begin(), s.end());
//here
    //free();

    elements = data.first;
    first_free = cap = data.second;
}

template<typename T>
inline
void Vector<T>::free() {
    // Fixme
    // destroy the old elements in reverse order
    for (int i = capacity() - 1; i >= 0; i--) {
        std::allocator_traits<decltype(alloc)>::destroy(alloc, &elements[i]);
    }
    // deallocate (cannot be called on a 0 pointer)
    alloc.deallocate(elements, capacity());

    elements = first_free = cap = 0;

}

template<typename T>
inline
Vector<T> &Vector<T>::operator=(std::initializer_list<T> il) {
    // HINT
    // copy allocates space and copies elements from the given range
    auto data = alloc_n_copy(il.begin(), il.end());

    free();   // destroy the elements in this object and free the space

    elements = data.first; // update data members to point to the new space
    first_free = cap = data.second;

    return *this;
}

template<typename T>
inline
Vector<T> &Vector<T>::operator=(Vector &&rhs) noexcept {
    // Fixme
    elements = std::move(rhs.elements);
    cap = std::move(rhs.cap);
    first_free = std::move(rhs.first_free);
    rhs.elements = rhs.first_free = rhs.cap = 0;
    return *this;
}

template<typename T>
inline
Vector<T> &Vector<T>::operator=(const Vector &rhs) {
    // Fixme
    auto data = alloc_n_copy(rhs.begin(), rhs.end());

    free();

    elements = data.first;
    first_free = cap = data.second;

    return *this;
}

template<typename T>
inline
void Vector<T>::reallocate() {
    // Fixme
    // we'll allocate space for twice as many elements as current size or 2 if size == 0
    int old_capacity = capacity();
    int alloc_size = old_capacity > 0 ? old_capacity * 2 : 2;
    // allocate new space
    T *new_space = alloc.allocate(alloc_size);
    // move the elements
    int count = 0;
    for (T *tmp = begin(); tmp != end(); tmp++) {
        std::allocator_traits<decltype(alloc)>::construct(alloc, &new_space[count++], *tmp);
    }

    // free the old space once we've moved the elements
    alloc.deallocate(elements, old_capacity);
    // update our data structure point to the new elements
    elements = new_space;
    first_free = new_space + old_capacity;
    cap = new_space + alloc_size;
}

template<typename T>
inline
void Vector<T>::push_back(const T &s) {
    chk_n_alloc(); // reallocates the Vector if necessary
    // Fixme
    // construct a copy "s" in the element to which first_free points
    std::allocator_traits<decltype(alloc)>::construct(alloc, first_free, s);// construct the copy
    first_free += 1;
}

template<typename T>
inline
void Vector<T>::push_back(T &&s) {
    chk_n_alloc(); // reallocates the Vector if necessary
    // move "s" in the element to which first_free points
    *first_free = std::move(s);
    first_free += 1;
}
