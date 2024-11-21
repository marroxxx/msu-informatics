#include "Complex.hpp"
#include "stack"

using std::stack;
using std::cerr;

Complex::Complex(double a, double b) {
    this->re = a;
    this->im = b;
}

Complex::Complex(const Complex &x) {
    this->re = x.re;
    this->im = x.im;
}

Complex::Complex(const string &x) {
    if (x.empty()) {
        this->re = 0;
        this->im = 0;
        return;
    }

    std::string s = x;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end()); 

    if (s == "i") {
        this->re = 0;
        this->im = 1;
        return;
    } else if (s == "-i") {
        this->re = 0;
        this->im = -1;
        return;
    } else if (s.back() == 'i') { 
        std::string imagPart = s.substr(0, s.size() - 1); 
        if (imagPart.empty() || imagPart == "+") {
            this->re = 0;
            this->im = 1;
        } else if (imagPart == "-") {
            this->re = 0;
            this->im = -1;
        } else {
            std::istringstream iss(imagPart);
            iss >> this->im; 
            this->re = 0;
        }
        return;
    }

    std::istringstream iss(s);
    double real = 0;
    char sign = '+';
    double imag = 0;

    iss >> real;

    if (iss >> sign) {
        if (sign == '+' || sign == '-') {
            iss >> imag;
            if (iss.peek() == 'i') { 
                iss.get(); 
                this->re = real;
                this->im = (sign == '-') ? -imag : imag;
                return;
            }
        }
    }

    this->re = real;
    this->im = 0; 
}

bool
Complex::first(char c) {
    return c == '+' || c == '-';
}

bool 
Complex::second(char c) {
    return c == '*' || c == '/';
}

bool
Complex::third(char c) {
    return c == '^';
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

Complex
Complex::calculate(string str) {
    deque<string> d;
    stack<char> op; 
    for (int i = 0; i < (int)str.length() - 1; ++i) {
        if (str[i] == '*' && str[i + 1] == '*') {
            str[i] = '^';
            str[i + 1] = ' ';
        }
    }
    for (int i = 0; i < (int)str.length(); ++i) {
        char c = str[i];

        if (isdigit(c) || (c == '-' && (i == 0 || str[i - 1] == '('))) {
            string num;
            if (c == '-') {
                num.push_back(c);
                ++i;
            }
            
            while (i < (int)str.length() && isdigit(str[i])) {
                num.push_back(str[i]);
                ++i;
            }
            
            if (i < (int)str.length() && str[i] == '.') {
                num.push_back(str[i]); 
                ++i;

                while (i < (int)str.length() && isdigit(str[i])) {
                    num.push_back(str[i]);
                    ++i;
                }
            }

            if (i < (int)str.length() && str[i] == 'i') {
                num.push_back(str[i]);
                ++i;
            }
            
            d.push_back(num);
            --i;
        } else if (c == 'i') {
            string num(1, c);
            d.push_back(num);
        } else if (first(c)) {
            while (!op.empty() && op.top() != '(') {
                string del(1, op.top());
                op.pop();
                d.push_back(del);
            }
            op.push(c);
        } else if (second(c)) {
            while (!op.empty() && (second(op.top()) || third(op.top()))) {
                string del(1, op.top());
                op.pop();
                d.push_back(del);
            }
            op.push(c);
        } else if (third(c)) {
            while (!op.empty() && third(op.top())) {
                string del(1, op.top());
                op.pop();
                d.push_back(del);
            }
            op.push(c);
        } else if (c == '(') {
            op.push(c);
        } else if (c == ')') {
            while (!op.empty() && op.top() != '(') {
                string del(1, op.top());
                op.pop();
                d.push_back(del);
            }
            if (op.empty()) {
                cerr << "an error in setting the brackets\n";
                exit(1);
            } else if (op.top() == '(') {
                op.pop();
            }
        } else if (c != ' ') {
            cerr << "Unknown operator: " << c << endl; 
            exit(1);
        }
    }
    while (!op.empty()) {
        if (op.top() == '(') {
            cerr << "an error in setting the brackets\n";
            exit(1);
        }
        string del(1, op.top());
        op.pop();
        d.push_back(del);
    }

    stack<Complex> digits;
    for (string s : d) {
        if (isdigit(s[0]) || (s[0] == '-' && s.length() > 1) || s[0] == 'i') {
            Complex num(s);
            digits.push(num);
        } else {
            if (digits.empty()) {
                cerr << "an error with stack\n";
                exit(1);
            }
            Complex a = digits.top();
            digits.pop();
            if (digits.empty()) {
                cerr << "an error with stack\n";
                exit(1);
            }
            Complex b = digits.top();
            digits.pop();
            char c = s[0];
            switch (c) {
                case '+':
                    digits.push(b + a);
                    break;
                case '-':
                    digits.push(b - a);
                    break;
                case '*':
                    digits.push(b * a);
                    break;
                case '/':
                    if (a == 0) {
                        cerr << "Division by zero\n";
                        exit(1);
                    }
                    digits.push(b / a);
                    break;
                case '^':
                    if (a.im == 0) {
                        digits.push(b ^ a.re);
                    } else {
                        cerr << "Raising to a complex degree\n";
                        exit(1);
                    }
                    break;
                default:
                    cerr << "Unknown operator(calculate error)\n";
                    exit(1);
            }
        }
    }
    return digits.top();
}