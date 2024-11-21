#ifndef CALCULATORGRIGORY_HPP
#define CALCULATORGRIGORY_HPP

#include <iostream>
#include <deque>
#include <string>

using std::cout;
using std::endl;
using std::deque;
using std::string;

template <typename T>
class Calculator {
    public:
        virtual T operator+(const T &x) const = 0; 
        virtual T operator-(const T &x) const = 0; 
        virtual T operator*(const T &x) const = 0; 
        virtual bool operator==(const T &x) const = 0; 
        virtual bool operator!=(const T &x) const = 0; 
        virtual T calculate(string s) = 0;
    protected:
        virtual bool first(char c) = 0;
        virtual bool second(char c) = 0;
        virtual bool third(char c) = 0;
};

#endif