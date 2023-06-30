#include <string>
#include <cstddef>

class HasPtr {
public:
    // constructor allocates a new string and a new counter,
    // which it sets to 1
    HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), i(0), use(new std::size_t(1)) {}

    // copy constructor copies all three data members
    // and increments the counter
    HasPtr(const HasPtr &p) :
            ps(p.ps), i(p.i), use(p.use) { ++*use; }

    HasPtr &operator=(const HasPtr &);

    ~HasPtr();

    // move constructor takes over the pointers from its argument
    // and makes the argument safe to delete
    HasPtr(HasPtr &&p) : ps(p.ps), i(p.i), use(p.use) {
        p.ps = 0;
        p.use = 0;
    }

    HasPtr &operator=(HasPtr &&);

private:
    std::string *ps;
    int i;
    std::size_t *use;  // member to track how many objects share *ps
};

HasPtr::~HasPtr() {
    // move constructor and move assignment operator move out the resource and invalidate the pointers
    // nothing to do in that case
    if (nullptr == use && nullptr == ps) { return; }

    if (--*use == 0) {   // if the reference count goes to 0
        delete ps;       // delete the string
        delete use;      // and the counter
    }
}

HasPtr &
HasPtr::operator=(HasPtr &&rhs) {
    if (this != &rhs) {
        if (--*use == 0) {   // do the work of the destructor
            delete ps;
            delete use;
        }
        ps = rhs.ps;         // do the work of the move constructor
        i = rhs.i;
        use = rhs.use;
        rhs.ps = 0;
        rhs.use = 0;
    }
    return *this;
}

HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use;  // increment the use count of the right-hand operand
    if (--*use == 0) {   // then decrement this object's counter
        delete ps;       // if no other users
        delete use;      // free this object's allocated members
    }
    ps = rhs.ps;         // copy data from rhs into this object
    i = rhs.i;
    use = rhs.use;
    return *this;        // return this object
}

HasPtr f(HasPtr hp) // HasPtr passed by value, so it is copied
{
    HasPtr ret;
    ret = hp;        // assignment copies the given HasPtr

    return ret;      // ret and hp are destroyed
}

int useCount() {
    HasPtr h("hi mom!");
    HasPtr h2 = h;  // no new memory is allocated,
    // h and h2 share the same underlying string
    return 0;
}