#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cstdint>
#include <cstdlib>

class Complex
{
private:
    double re;
    double im;
public:
    Complex(double a = 0, double b = 0);
    Complex(const Complex &x);
    Complex operator+(const Complex &x) const;
    Complex operator-(const Complex &x) const;
    Complex operator*(const Complex &x) const;
    Complex operator/(const Complex &x) const;
    bool operator==(const Complex &x) const;
    bool operator!=(const Complex &x) const;
    friend std::ostream &operator<<(std::ostream &out, const Complex &x);
};

#endif