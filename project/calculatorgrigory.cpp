#include <iostream>
#include <deque>
#include <stack>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath> 
#include <memory>
#include "BigInt.hpp"
#include "Complex.hpp"


using std::cin;
using std::cout;
using std::stack;
using std::deque;
using std::string;
using std::cerr;
using std::endl;


int 
main(void) {
    string s;
    std::unique_ptr<BigInt>bigint = std::make_unique<BigInt>(); 
    std::unique_ptr<Complex>complex = std::make_unique<Complex>();
    bool is_complex = false;
    while (std::getline(std::cin, s)) {
        if (s.empty()) {
            break;
        }
        if (s.find('i') != std::string::npos || s.find('.') != std::string::npos) {
            is_complex = 1;
        }
        if (is_complex) {
            std::cout << complex->calculate(s) << endl;
        } else {
            std::cout << bigint->calculate(s) << endl;
        }
        is_complex = 0;
    }
    return 0;
}
