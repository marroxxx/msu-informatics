#include "pointers.hpp"
#include <vector>

using std::vector;

namespace pointers {
    template <typename T>
    unique_ptr<T>::unique_ptr(T &&x) {
        
    }

    template <typename T> 
    T *unique_ptr<T>::operator->() const {
        return this->data;
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
