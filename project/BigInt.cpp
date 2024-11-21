#include "BigInt.hpp"
#include <sstream>
#include <stack>
#include <stdlib.h>

using std::stack;
using std::cerr;

BigInt::BigInt(const BigInt &x) {
    this->digits = x.digits;
}

BigInt::BigInt(int32_t a) { 
    int32_t digit = static_cast<int32_t>(a);
    if (a < 0) {
        digit = static_cast<int32_t>(~(std::abs(a)) + 1);
    }
    digits.push_back(digit); 
    if (digits.empty()) {
        digits.push_back(0);
    }
}

BigInt::BigInt(const string &s) {
    string cur = "";
    if (s[0] != '-') {
        int value;
        int c = 8 - (int)s.length() % 8;
        for (size_t i = 0; i < (size_t)s.length(); ++i) {
            cur.push_back(s[i]);
            std::stringstream ss;
            if ((i + 1 + c) % 8 == 0) {
                //std::cout << cur << std::endl;
                ss << std::hex << cur;
                ss >> value;
                this->digits.push_back(value);
                cur = "";
            }
        }
        if (cur != "") {
            std::stringstream ss;
            ss << std::hex << cur;
            ss >> value;
            this->digits.push_back(value);
        }  
        std::reverse(this->digits.begin(), this->digits.end());
    } else {
        int value;
        int c = 8 - (int)s.length() % 8;
        for (size_t i = 1; i < (size_t)s.length(); ++i) {
            cur.push_back(s[i]);
            std::stringstream ss;
            if ((i + 1 + c) % 8 == 0) {
                //std::cout << cur << std::endl;
                ss << std::hex << cur;
                ss >> value;
                value = ~value + 1;
                this->digits.push_back(value);
                cur = "";
            }
        }
        if (cur != "") {
            std::stringstream ss;
            ss << std::hex << cur;
            ss >> value;
            value = ~value + 1;
            this->digits.push_back(value);
        }  
        std::reverse(this->digits.begin(), this->digits.end());
    }
}

BigInt 
BigInt::operator+(const BigInt& x) const {
    int carry = 0;
    int max_len = std::max(this->digits.size(), x.digits.size());
    BigInt res;
    res.digits.resize(max_len);
    
    for (int i = 0; i < max_len; ++i) {
        int64_t this_num = (i < this->digits.size()) ? this->digits[i] : 0;
        int64_t x_num = (i < x.digits.size()) ? x.digits[i] : 0;
        int64_t sum = this_num + x_num + carry;
        
        if (sum > INT32_MAX) {
            carry = 1;
            res.digits[i] = (int32_t)(sum - INT32_MAX - 1);
        } else if (sum <= INT32_MIN) {
            carry = -1;
            res.digits[i] = (int32_t)(sum + INT32_MAX + 1);
        } else {
            carry = 0;
            res.digits[i] = sum;
        }
    }

    if (carry != 0) {
        res.digits.push_back(carry);
    }

    while (!res.digits.empty() && res.digits.back() == 0) {
        res.digits.pop_back();
    }

    if (res.digits.empty()) {
        res.digits.push_back(0);
    }

    return res;
}

std::ostream &
operator<<(std::ostream &out, const BigInt &x) {
    /*
    out << "Bits: ";
    for (int i = x.digits.size() - 1; i >= 0; --i) {
        std::bitset<BASE_LEN> binary(x.digits[i]);
        out << binary;
        out << " ";
    }
    out << std::endl << "Digits: ";
    for (int i = x.digits.size() - 1; i >= 0; --i) {
        out << x.digits[i];
        out << " ";
    }
    out << std::endl << "Hex: ";
    */
    for (int i = x.digits.size() - 1; i >= 0; --i) {
        out << std::hex << x.digits[i];
    }
    return out;
}

BigInt 
BigInt::operator-(const BigInt &a) const {
    BigInt a_copy = a;
    for (int i = 0; i < a_copy.digits.size(); ++i) {
        a_copy.digits[i] = ~a_copy.digits[i] + 1;
    }
    return *this + a_copy;
} 

bool 
BigInt::operator>(const BigInt &x) const {
    int max_len = std::max(this->digits.size(), x.digits.size());
    for (int i = max_len - 1; i >= 0; --i) {
        int this_num = (i < this->digits.size()) ? this->digits[i] : 0;
        int x_num = (i < x.digits.size()) ? x.digits[i] : 0;
        if (this_num > x_num) {
            return true;
        } else if (this_num < x_num) {
            return false;
        }
    }
    return false;
}

bool 
BigInt::operator<(const BigInt &x) const {
    int max_len = std::max(this->digits.size(), x.digits.size());
    for (int i = max_len - 1; i >= 0; --i) {
        int this_num = (i < this->digits.size()) ? this->digits[i] : 0;
        int x_num = (i < x.digits.size()) ? x.digits[i] : 0;
        if (this_num < x_num) {
            return true;
        } else if (this_num > x_num) {
            return false;
        }
    }
    return false;
}

bool 
BigInt::operator==(const BigInt &x) const {
    int max_len = std::max(this->digits.size(), x.digits.size());
    for (int i = max_len - 1; i >= 0; --i) {
        int this_num = (i < this->digits.size()) ? this->digits[i] : 0;
        int x_num = (i < x.digits.size()) ? x.digits[i] : 0;
        if (this_num != x_num) {
            return false;
        } 
    }
    return true;
}

bool 
BigInt::operator!=(const BigInt &x) const {
    return !(*this == x);
}

bool
BigInt::operator>=(const BigInt &x) const {
    return *this > x || *this == x;
}

bool
BigInt::operator<=(const BigInt &x) const {
    return *this < x || *this == x;
}

BigInt BigInt::operator*(const BigInt &x) const {
    BigInt res;
    res.digits.clear();
    std::vector<int64_t> dig(this->digits.size() + x.digits.size(), 0);

    for (size_t i = 0; i < this->digits.size(); ++i) {
        for (size_t j = 0; j < x.digits.size(); ++j) {
            dig[i + j] += static_cast<int64_t>(this->digits[i]) * x.digits[j];
            if (dig[i + j] > INT32_MAX) {
                dig[i + j + 1] += dig[i + j] / ((int64_t)INT32_MAX + 1);
                dig[i + j] %= ((int64_t)INT32_MAX + 1);
            }
        }
    }

    for (size_t i = 0; i < dig.size() - 1; ++i) {
        if (dig[i] > INT32_MAX) {
            dig[i + 1] += dig[i] / ((int64_t)INT32_MAX + 1);
            dig[i] %= ((int64_t)INT32_MAX + 1);
        }
    }

    if (dig.back() > INT32_MAX) {
        dig.push_back(dig.back() / ((int64_t)INT32_MAX + 1));
        dig[dig.size() - 2] %= ((int64_t)INT32_MAX + 1);
    }

    for (int64_t elem : dig) {
        res.digits.push_back(static_cast<int32_t>(elem));
    }

    while (!res.digits.empty() && res.digits.back() == 0) {
        res.digits.pop_back();
    }

    if (res.digits.empty()) {
        res.digits.push_back(0); 
    }

    return res;
}

bool 
BigInt::first(char c) {
    return c == '+' || c == '-';
}

bool 
BigInt::second(char c) {
    return c == '*';
}

bool 
BigInt::third(char c) {
    return c == '^';
}

BigInt
BigInt::calculate(string str) {
    deque<string> d;
    std::stack<char> op; 
    for (int i = 0; i < (int)str.length() - 1; ++i) {
        if (str[i] == '*' && str[i + 1] == '*') {
            str[i] = '^';
            str[i + 1] = ' ';
        }
    }
    for (int i = 0; i < (int)str.length(); ++i) {
        char c = str[i];
        if (isxdigit(str[i]) || (c == '-' && (i == 0 || str[i-1] == '('))) {
            string num;
            if (c == '-') {
                num.push_back(c);
                ++i;
            }
            while (i < (int)str.length() && isxdigit(str[i])) {
                num.push_back(str[i]);
                ++i;
            }
            d.push_back(num);
            --i;
        } else if (first(c)) {
            while (!op.empty() && op.top() != '(') {
                string del(1, op.top());
                op.pop();
                d.push_back(del);
            }
            op.push(c);
        } else if (second(c)) {
            while (!op.empty() && (second(op.top()))) {
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
            cerr << "Unknown operator\n";
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
    stack<BigInt> digits;
    for (string s : d) {
        if (isxdigit(s[0]) || (s[0] == '-' && s.length() > 1)) {
            BigInt num(s);
            digits.push(num);
        } else {
            if (digits.empty()) {
                cerr << "an error with stack\n";
                exit(1);
            }
            BigInt a = digits.top();
            digits.pop();
            if (digits.empty()) {
                cerr << "an error with stack\n";
                exit(1);
            }
            BigInt b = digits.top();
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
                default:
                    cerr << "Unknown operator (calculate error)\n";
                    exit(1);
            }
        }
    }
    return digits.top();
}