#include "Complex.hpp"

Complex::Complex(double a, double b) {
    this->re = a;
    this->im = b;
}

Complex::Complex(const Complex &x) {
    this->re = x.re;
    this->im = x.im;
}

Complex 
Complex::operator+(const Complex &x) const {
    Complex res;
    res.re = this->re + x.re;
    res.im = this->im + x.im;
    return res;
}

Complex 
Complex::operator-(const Complex &x) const {
    Complex res;
    res.re = this->re - x.re;
    res.im = this->im - x.im;
    return res;
}

Complex 
Complex::operator*(const Complex &x) const {
    Complex res;
    res.re = this->re * x.re - this->im * x.im;
    res.im = this->im * x.re + this->re * x.im;
    return res;
}

Complex
Complex::operator/(const Complex &x) const {
    Complex res;
    if (x.re * x.re + x.im * x.im != 0) {
        res.re = (this->re * x.re + this->im * x.im) / (x.re * x.re + x.im * x.im);
        res.im = (this->im * x.re - this->re * x.im) / (x.re * x.re + x.im * x.im);
    } else {
        std::cerr << "err: division by zero" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    res.re = (x.re * x.re + x.im * x.im != 0) ? (this->re * x.re + this->im * x.im) / (x.re * x.re + x.im * x.im) : 0;
    res.im = (this->im * x.re - this->re * x.im) / (x.re * x.re + x.im * x.im);
    return res;
}

bool 
Complex::operator==(const Complex &x) const {
    return this->re == x.re && this->im == x.im;
}

bool 
Complex::operator!=(const Complex &x) const {
    return !(*this == x);
}

std::ostream &
operator<<(std::ostream &out, const Complex &x) {
    std::cout << x.re;
    if (x.im >= 0) {
        std::cout << " + " << x.im << "i";
    } else {
        std::cout << " - " << -x.im << "i";
    }
    return out;
}

int 
main(void) {
    Complex x;
    Complex y(1, 4);
    std::cout << y / x << std::endl;
    return 0;
}