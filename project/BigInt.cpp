#include "BigInt.hpp"

BigInt::BigInt(const BigInt &x) {
    this->digits = x.digits;
}

BigInt::BigInt(int a) {
    if (a <= 0) {
        this->digits = vector <int32_t> (BASE_LEN, INT32_MAX);
        this->digits[0] -= std::abs(a);
        int carry = 1;
        for (int i = 0; i < BASE_LEN; ++i) {
            if (carry == 1 && this->digits[i] == INT32_MAX) {
                this->digits[i] = 0;
            } else {
                this->digits[i] += carry;
                carry = 0;
            }
        }
    }
    if (a > 0) {
        this->digits = vector <int32_t> (BASE_LEN, 0);
        this->digits[0] = a;
    }
}

void
BigInt::neg() { 
    for (int i = 0; i < BASE_LEN; ++i) {
        this->digits[i] = INT32_MAX - std::abs(this->digits[i]);
    }
    int carry = 1;
    for (int i = 0; i < BASE_LEN; ++i) {
        if (carry == 1 && this->digits[i] == INT32_MAX) {
            this->digits[i] = 0;
        } else {
            this->digits[i] += carry;
            carry = 0;
        }
    }
}

BigInt &
BigInt::add(const BigInt &b) {
    int carry = 0;
    for (int i = 0; i < BASE_LEN; ++i) {
        if ((int64_t)this->digits[i] + (int64_t)b.digits[i] + carry > INT32_MAX) {
            this->digits[i] = ((int64_t)this->digits[i] + (int64_t)b.digits[i] + carry) - INT32_MAX - 1;
            carry = 1;
        } else {
            this->digits[i] += (b.digits[i] + carry);
            carry = 0;
        }
    }
    return *this;
}    

BigInt &
BigInt::sub(const BigInt &a) {
    this->neg();
    this->add(a);
    this->neg();
    return *this;
}

void 
BigInt::print() {
    for (int i = 0; i < BASE_LEN; ++i) {
        std::cout << this->digits[i] << " ";
    }
    std::cout << std::endl;
}

int
main(void) {
    BigInt num1(INT32_MAX / 2);
    BigInt num2(1);
    num1.print();
    num2.print();
    num2.sub(num1);
    num2.neg();
    num2.print();
    return 0;
}