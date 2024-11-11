#include "Pointers.hpp"
#include <vector>

using std::vector;

namespace pointers {
    template <typename T>
    unique_ptr<T>::unique_ptr(T &&x) {
        this->data = new T(x);
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(T *x) {
        this->data = x;
    }

    template <typename T>
    unique_ptr<T>::unique_ptr(unique_ptr<T>&& x) { 

    }

    template <typename T>
    unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr<T>&& x) {
        if (this != x) {
            delete this;
            this->data;
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

int 
main() {
    return 0;
}