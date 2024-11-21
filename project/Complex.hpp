#ifndef COMPLEX_H 
#define COMPLEX_H 
 
#include <string>  
#include <thread>
#include <string>  
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "calculatorgrigory.hpp"

using std::string;  
  
class Complex : public Calculator<Complex> {  
private:  
    double re; 
    double im; 
protected:
    bool first(char c) override;
    bool second(char c) override;
    bool third(char c) override;
public:  
    Complex(double re = 0, double im = 0); 
    Complex(const Complex &x);  
    Complex(const string &s);  
      
    Complex operator+(const Complex &x) const override;  
    Complex operator+(const int x) const;  
    Complex operator-(const Complex &x) const override;  
    Complex operator-(const int x) const;  
    Complex operator*(const Complex &x) const override;  
    Complex operator*(const int x) const;  
  
    Complex operator/(const Complex &x) const;  
    Complex operator/(const int x) const;  
    //Complex operator^(const Complex &x) const;  
    Complex operator^(const int x) const;  
  
    Complex operator+() const;  
    Complex operator-() const;  
   
    bool operator==(const Complex &x) const override;  
    bool operator!=(const Complex &x) const override;  
      
    
    friend std::ostream &operator<<(std::ostream &out, const Complex &x);  
    Complex calculate(string s) override;

}; 
 
#endif