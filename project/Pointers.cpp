#include "Pointers.hpp"
#include <vector>
#include <iostream>

using std::vector;

namespace pointers {

    template <typename T>
    unique_ptr<T>::unique_ptr() {
        this->data = nullptr;
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(T &&x) {
        this->data = std::move(x);
    }


    template <typename T>
    unique_ptr<T>::unique_ptr(T *x) {
        this->data = x;
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(unique_ptr<T>&& x) { 
        this->data = x.data;
        x.data = nullptr;
        delete x.data;
    }

    template <typename T>
    unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr<T>&& x) {
        if (this != &x) {
            delete(this->data);
            this->data = x.data;
            x.data = nullptr;
            delete(x.data);
        }
        return *this;
    }

    template <typename T> 
    T *unique_ptr<T>::operator->() const {  
        return this->data;
    }

    template <typename T>
    T &unique_ptr<T>::operator*() const {
        return *this->data;
    }

    template <typename T>
    unique_ptr<T>::~unique_ptr() {
        delete this->data;
    }
}


struct Test {
    int value;

    Test(int v) : value(v) {
        std::cout << "Test(int v) constructor, value = " << value << std::endl;
    }

    ~Test() {
        std::cout << "Test destructor, value = " << value << std::endl;
    }

    void display() {
        std::cout << "Test::display(), value = " << value << std::endl;
    }
};


int main() {
    pointers::unique_ptr<Test> p1(new Test(42));

    p1->display();      
    (*p1).display();     

    pointers::unique_ptr<Test> p2(std::move(p1));

    if (p1.operator->() == nullptr) {
        std::cout << "p1 is null after move" << std::endl;
    }

    p2->display();

    pointers::unique_ptr<Test> p3;
    p3 = std::move(p2);

    if (p2.operator->() == nullptr) {
        std::cout << "p2 is null after move assignment" << std::endl;
    }

    p3->display();

    p3 = pointers::unique_ptr<Test>(new Test(100));

    p3->display();

    return 0;
}
