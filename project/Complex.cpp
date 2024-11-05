#include "Complex.hpp"

Complex::Complex(double a, double b) {
    this->re = a;
    this->im = b;
}

Complex::Complex(const Complex &x) {
    this->re = x.re;
    this->im = x.im;
}

Complex::Complex(const std::string &x) {
    if (x.empty()) {
        this->re = 0;
        this->im = 0;
        return;
    }
    std::string s = x;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    double real, imag;
    char sign;
    std::istringstream iss(s);
    iss >> real >> sign >> imag;
    this->re = real;
    this->im = sign == '-' ? -imag : imag;
}

Complex 
Complex::operator+(const Complex &x) const {
    Complex res;
    res.re = this->re + x.re;
    res.im = this->im + x.im;
    return res;
}

Complex 
Complex::operator+(const int x) const {
    Complex res;
    res.re = this->re + x;
    res.im = this->im;
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
Complex::operator-(const int x) const {
    Complex res;
    res.re = this->re - x;
    res.im = this->im;
    return res;
}

Complex 
Complex::operator*(const Complex &x) const {
    Complex res;
    res.re = this->re * x.re - this->im * x.im;
    res.im = this->re * x.im + this->im * x.re;
    return res;
}

Complex 
Complex::operator*(const int x) const {
    Complex res;
    res.re = this->re * x;
    res.im = this->im * x;
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

Complex 
Complex::operator/(const int x) const {
    Complex res;
    if (x != 0) {
        res.re = this->re / x;
        res.im = this->im / x;
    } else {
        std::cerr << "err: division by zero" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return res;
}

Complex 
Complex::operator^(const int x) const {
    Complex res;
    double mod = std::sqrt(this->re * this->re + this->im * this->im);
    mod = std::pow(mod, x);
    double phi = std::atan2(this->im, this->re);
    res.re = mod * std::cos(phi * x);
    res.im = mod * std::sin(phi * x);
    return res;
}

Complex 
Complex::operator+() const {
    return *this;
}

Complex 
Complex::operator-() const {
    Complex res;
    res.re = -this->re;
    res.im = -this->im;
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
    bool is_zero = true;
    if (x.re != 0) {
        std::cout << x.re;
        is_zero = false;
    } 
    if (x.im > 0) {
        std::cout << " + " << x.im << "i";
        is_zero = false;
    } else if (x.im < 0) {
        std::cout << " - " << -x.im << "i";
        is_zero = false;
    }
    if (is_zero) {
        std::cout << 0;
    }
    return out;
}

int 
main(void) {
    Complex a("1e-9 - 2e-8i");
    Complex b("");
    std::cout << a << std::endl;
    return 0;
}