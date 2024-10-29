#include "BigInt.hpp"
#include <sstream>

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
                std::cout << cur << std::endl;
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
                std::cout << cur << std::endl;
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

int 
main(void) {
    BigInt num1("ffffffff");
    BigInt num2("2");
    BigInt num3(INT_MIN);
    BigInt num4(1);
    std::cout << num3 - num4 + num1 + num2 << std::endl;
    //std::cout << num1 + num2 - num1 - num1 << std::endl;
    return 0;
}
