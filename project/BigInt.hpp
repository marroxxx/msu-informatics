#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector> 
#include <cstdint> 
#include <string> 
#include <iostream>
#include <bitset>
#include <algorithm>
#include "calculatorgrigory.hpp"

using std::vector; 
using std::string; 
 
enum {
    BASE_LEN = 32
};

class BigInt : public Calculator<BigInt> { 
    public:
        BigInt(const BigInt&);
        BigInt(int32_t a = 0);
        BigInt(const string&);
        BigInt operator+(const BigInt &x) const override;
        BigInt operator-(const BigInt &x) const override;
        BigInt operator*(const BigInt &x) const override;
        friend std::ostream &operator<<(std::ostream &out, const BigInt &x);
        bool operator==(const BigInt &x) const override;
        bool operator>(const BigInt &x) const;
        bool operator<(const BigInt &x) const;
        bool operator>=(const BigInt &x) const;
        bool operator<=(const BigInt &x) const;
        bool operator!=(const BigInt &x) const override;
        BigInt calculate(string) override;
    protected:
        bool first(char c) override;
        bool second(char c) override;
        bool third(char c) override;
    private: 
        vector<int32_t> digits; 
};

#endif