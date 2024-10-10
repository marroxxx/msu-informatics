#ifndef BIGINT_HPP
#define BIGINT_HPP


#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using std::string;
using std::vector;

enum {
    BASE_LEN = 8
};

class BigInt {
    private:
        vector <int32_t> digits;
    public:
        BigInt(int a);
        BigInt(const BigInt &x);
        void neg();
        BigInt &add(const BigInt &a);
        BigInt &sub(const BigInt &a);
        BigInt &mul(const BigInt &a);
        BigInt &div(const BigInt &a);
        BigInt &mod(const BigInt &a);
        BigInt &pow(const BigInt &a);
        void print();
};

#endif