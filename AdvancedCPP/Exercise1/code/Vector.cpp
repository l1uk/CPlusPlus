#include "Vector.h"

Vector::Vector(size_t rows, double initValue) {
    this->data = new double[rows]();
    this->rows_ = rows;
    std::fill(this->data, this->data + this->rows_, initValue);
}

Vector::Vector(size_t rows) {
    this->data = new double[rows]();
    this->rows_ = rows;
}

Vector::Vector(std::initializer_list<double> l) {
    size_t rows = l.size();
    this->data = new double[rows]();
    this->rows_ = rows;
    std::copy(l.begin(), l.end(), this->data);
}

// destructor
Vector::~Vector() {
    delete[] this->data;
    this->data = nullptr;
}

// Copy constructor
Vector::Vector(const Vector &other) {
    this->rows_ = other.rows_;
    this->data = new double[other.rows_]();
    std::copy(other.data, other.data + other.rows_, this->data);
}

// Move constructor
Vector::Vector(Vector &&other) noexcept {
    this->rows_ = std::move(other.rows_);
    this->data = std::move(other.data);
    other.data = 0;
}

// Copy assignment operator
Vector &Vector::operator=(const Vector &other) {
    if (this->rows_ != other.rows_) {
        this->rows_ = other.rows_;
        delete[] this->data;
        this->data = new double[this->rows_]();
    }
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = other.data[i];
    }
    return *this;
}

// Move assignment operator
Vector &Vector::operator=(Vector &&other) noexcept {
    delete[] this->data;
    this->data = 0;
    this->rows_ = other.rows_;
    this->data = other.data;
    other.data = 0;
    return *this;
}

void swap(Vector &a, Vector &b) {
    std::swap(a, b);
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
    assert(this->size() == b.size());
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = this->data[i] + b.data[i];
    }
    return *this;
}

Vector Vector::operator+(const Vector &b) const {
    Vector ret(*this);
    ret += b;
    return ret;
}

Vector &Vector::operator-=(const Vector &b) {
    assert(this->size() == b.size());
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = this->data[i] - b.data[i];
    }
    return *this;
}

Vector Vector::operator-(const Vector &b) const {
    Vector ret(*this);
    ret -= b;
    return ret;
}

Vector Vector::operator*(const Vector &b) const {
    Vector ret(*this);
    ret *= b;
    return ret;
}

Vector &Vector::operator*=(const Vector &b) {
    assert(this->size() == b.size());
    for (size_t i = 0; i < this->rows_; i++) {
        this->data[i] = this->data[i] * b.data[i];
    }
    return *this;
}

// print matrixelements to stream
std::ostream &operator<<(std::ostream &outputStream, const Vector &m) {
    for (size_t i = 0; i < m.rows_; i++) {
        outputStream << m.data[i];
        if (i != m.rows_ - 1) {
            outputStream << "   ";
        }
    }
    return outputStream;
}

// read matrixelements from stream
std::istream &operator>>(std::istream &inputStream, Vector &m) {
    for (size_t i = 0; i < m.rows_; i++) {
        if (!(inputStream >> m.data[i])) {
            throw new std::runtime_error("Error in double parsing!");
        }
    }
    return inputStream;
}

double *Vector::begin() {
    return this->data;
}

double *Vector::end() {
    return this->data + this->rows_;
}

const double *Vector::begin() const {
    const double *ret = this->data;
    return ret;
}

const double *Vector::end() const {
    const double *ret = this->data + this->rows_;
    return ret;
}

size_t Vector::size() const {
    return this->rows_;
}

double Vector::dot(const Vector &b) const {
    Vector a_mul_b = *this * b; // product of two vectors
    return std::accumulate(a_mul_b.begin(), a_mul_b.end(), (double) 0.0, std::plus<double>()); // sum of products
}