#include <cstdlib>
#include <iostream>
#include <list>

class Screen0 {

private:
    size_t size;
    int *data;

public:

    Screen0() : data(nullptr), size(0) {
        std::cout << "default constructor" << std::endl;
    }

    Screen0(size_t size_, int color) : color(color), size(size_),
                                       data(new int[size]) {
        std::cout << "size,col constructor" << std::endl;
    }

    Screen0(const Screen0 &) {
        std::cout << "copy constructor" << std::endl;
    }

    Screen0 &operator=(Screen0 &) {
        std::cout << "copy assignment" << std::endl;
        return *this;
    }

    Screen0(Screen0 &&) {
        std::cout << "move constructor" << std::endl;
    }

    Screen0 &operator=(Screen0 &&) {
        std::cout << "move assignment" << std::endl;
        return *this;
    }

    ~Screen0() {
        std::cout << "destructor" << std::endl;
        if (data != nullptr)
            delete[] data;
    }

    int getsize() const {
        std::cout << "getsize const" << std::endl;
        return size;
    }

    void setsize(const int &size) { this->size = size; }

    int getdata(int i) { return data[i]; }

    int color;
};


int copyControl() {
    Screen0 *s = new Screen0(); // default constructor
    Screen0 s1(12, 12); // size,col constructor

    Screen0 s2(s1); // copy constructor
    Screen0 s3 = s2; // copy constructor

    s2 = s1; // copy assignment

    Screen0 move = std::move(s2); // move constructor

    move = std::move(s2); // move assignment

    return 0;
}

