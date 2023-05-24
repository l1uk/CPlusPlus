#include "Vector.h"

Vector::Vector(size_t rows, double initValue) {
    this->data = new double[rows]();
    this->rows_ = rows;
    for (size_t i = 0; i < rows; i++)
        this->data[i] = initValue;
}

Vector::Vector(size_t rows) {
    this->data = new double[rows]();
    this->rows_ = rows;
}

Vector::Vector(std::initializer_list<double> l) {
    size_t rows = l.size();
    this->data = new double[rows]();
    this->rows_ = rows;
    std::initializer_list<double>::iterator it = l.begin();
    int count = 0;
    for (it = l.begin(); it != l.end(); it++) {
        this->data[count++] = *it;
    }
}

// destructor
Vector::~Vector() {
    delete[] this->data;
}

// Copy constructor
Vector::Vector(const Vector &other) {
    this->rows_ = other.rows_;
    this->data = new double[this->rows_]();
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = other.data[i];
    }
}

// Move constructor
Vector::Vector(Vector &&other) noexcept {
    this->rows_ = other.rows_;
    this->data = other.data;
    other.data = 0;
}

// Copy assignment operator
Vector &Vector::operator=(const Vector &other) {
    if (this->rows_ != other.rows_) {
        this->rows_ = other.rows_;
        this->data = new double[this->rows_]();
    }
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = other.data[i];
    }
    return *this;
}

// Move assignment operator
Vector &Vector::operator=(Vector &&other) noexcept {
    this->rows_ = other.rows_;
    this->data = other.data;
    other.data = 0;
    return *this;
}

void swap(Vector &a, Vector &b) {
    Vector tmp = a;
    for (size_t i = 0; i < a.rows_; i++) {
        a[i] = b[i];
        b[i] = tmp[i];
    }
}

bool Vector::operator==(const Vector &b) const {
    if (this->rows_ != b.rows_) {
        return false;
    }
    for (size_t i = 0; i < this->rows_; i++) {
        if (this->data[i] != b.data[i]) { return false; }
    }

    return true;
}

bool Vector::operator!=(const Vector &b) const {
    if (this->rows_ != b.rows_) {
        return true;
    }
    return !(*this == b);
}

Vector &Vector::operator+=(const Vector &b) {
    //FIXME
    return *this;
}

Vector Vector::operator+(const Vector &b) const {
    //FIXME
    return *this;
}

Vector &Vector::operator-=(const Vector &b) {
    //FIXME
    return *this;
}

Vector Vector::operator-(const Vector &b) const {
    //FIXME
    return *this;
}

Vector Vector::operator*(const Vector &b) const {
    //FIXME
    return *this;
}

Vector &Vector::operator*=(const Vector &b) {
    //FIXME
    return *this;
}

// print matrixelements to stream
std::ostream &operator<<(std::ostream &outputStream, const Vector &m) {
    //FIXME
    return outputStream;
}

// read matrixelements from stream
std::istream &operator>>(std::istream &inputStream, Vector &m) {
    //FIXME
    return inputStream;
}

double *Vector::begin() {
    // return &this->data[0];
    return nullptr;
}

double *Vector::end() {
    // return &this->data[this->rows_];
    return nullptr;
}

const double *Vector::begin() const {
    // return begin();
    return nullptr;
}

const double *Vector::end() const {
    // return end();
    return nullptr;
}

size_t Vector::size() const {
    return this->rows_;
}

double Vector::dot(const Vector &b) const {
    //return std::accumulate(this->begin(), this->end(), 0);
    return 0;
}