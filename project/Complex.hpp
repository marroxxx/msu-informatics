#ifndef COMPLEX_H 
#define COMPLEX_H 
 
#include <string>  
#include <thread>
#include <string>  
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>

using std::string;  
  
class Complex {  
private:  
    double re; 
    double im; 
public:  
    Complex(double re = 0, double im = 0); 
    Complex(const Complex &x);  
    Complex(const string &s);  
      
    Complex operator+(const Complex &x) const;  
    Complex operator+(const int x) const;  
    Complex operator-(const Complex &x) const;  
    Complex operator-(const int x) const;  
    Complex operator*(const Complex &x) const;  
    Complex operator*(const int x) const;  
  
    Complex operator/(const Complex &x) const;  
    Complex operator/(const int x) const;  
    //Complex operator^(const Complex &x) const;  
    Complex operator^(const int x) const;  
  
    Complex operator+() const;  
    Complex operator-() const;  
  
    //bool operator>(const Complex &x) const;  
    //bool operator<(const Complex &x) const;  
    //bool operator>=(const Complex &x) const;  
    //bool operator<=(const Complex &x) const;  
    bool operator==(const Complex &x) const;  
    bool operator!=(const Complex &x) const;  
      
    friend std::ostream &operator<<(std::ostream &out, const Complex &x);  
}; 
 
#endif