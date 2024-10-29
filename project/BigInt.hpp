#ifndef BIGINT_HPP
#define BIGINT_HPP


#include <vector> 
#include <cstdint> 
#include <string> 
#include <iostream>
#include <bitset>
#include <algorithm>

using std::vector; 
using std::string; 
 
enum {
    BASE_LEN = 32
};

class BigInt { 
private: 
    vector<int32_t> digits; 
public: 
    BigInt(int32_t a = 0); 
    BigInt(const BigInt &x); 
    BigInt(const string &s); 
    
    BigInt operator+(const BigInt &x) const; 
    //BigInt operator+(const int x) const; 
    BigInt operator-(const BigInt &x) const; 
    //BigInt operator-(const int x) const; 
    BigInt operator*(const BigInt &x) const; 
    //BigInt operator*(const int x) const; 
 
    //BigInt operator/(const BigInt &x) const; 
    //BigInt operator/(const int x) const; 
    //BigInt operator%(const BigInt &x) const; 
    //BigInt operator%(const int x) const; 
    //BigInt operator^(const BigInt &x) const; 
    //BigInt operator^(const int x) const; 
 
    //BigInt &operator++(); 
    //BigInt &operator--(); 
    //BigInt operator++(int); 
    //BigInt operator--(int); 
     
 
 
    BigInt operator+() const; 
    BigInt operator-() const; 
 
    bool operator>(const BigInt &x) const; 
    bool operator<(const BigInt &x) const; 
    bool operator>=(const BigInt &x) const; 
    bool operator<=(const BigInt &x) const; 
    bool operator==(const BigInt &x) const; 
    bool operator!=(const BigInt &x) const; 
     
    friend std::ostream &operator<<(std::ostream &out, const BigInt &x); 
     
    //BigInt &mul(const BigInt &x) const; 
    //BigInt &div(const BigInt &x) const; 
    //BigInt &mod(const BigInt &x) const; 
    //BigInt &pow(const BigInt &x) const; 
};

#endif