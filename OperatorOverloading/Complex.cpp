#include <iostream>

using namespace std;

class complex {
    double re, im;
public:
    complex(double r = 0.0, double i = 0.0) : re(r), im(i) {};

    friend complex operator+(const complex &, const complex &);

    friend complex operator*(const complex &, const complex &);

    friend ostream &operator<<(ostream &, const complex &);

    friend istream &operator>>(istream &, complex &);

    ~complex() {
        cout << "morte del complesso " << *this << " all'indirizzo ->" << this << '\n';
    };
};

ostream &operator<<(ostream &s, const complex &z) {
    return s << '(' << z.re << ',' << z.im << ')';
};


istream &operator>>(istream &s, complex &z) {
    char a;
    return s >> z.re >> a >> z.im;
};

void f(void) {
    complex a(1, 3.1);
    complex b(1.2, 2);
    complex c = b;
    a = b + c;//uso abbreviato
    b = complex(5, 6);
    cout << "dopo la prima espressione\n";
    b = operator+(a, c);//uso esplicito
    cout << "dopo la seconda espressione\n";
    b = b + c * a;
    cout << "dopo la terza espressione\n";
    cout << b << '\n';
    c = a * b + complex(1, 2);
    cout << 1 + c << '\n';
}

complex operator+(const complex &a, const complex &b) {
    return complex(a.re + b.re, a.im + b.im);
};

complex operator*(const complex &a, const complex &b) {
    return complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
};

int complex_ex() {
    complex c;
    cout << "immetti un complesso (parte reale, parte immaginaria)->";
    cin >> c;
    cout << c << '\n';
    f();
    return 0;
}
