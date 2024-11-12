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

    template <typename T> 
    shared_ptr<T>::shared_ptr() {
        this->data = nullptr;
        this->num_shared = new size_t(0);
        this->num_weak = new size_t(0);
    }

    template <typename T> 
    shared_ptr<T>::shared_ptr(T &&x) {
        this->data = std::move(x);
        this->num_shared = new size_t(1);
    }

    template <typename T> 
    shared_ptr<T>::shared_ptr(T *x) {
        this->data = x;
        this->num_shared = new size_t(1);
        this->num_weak = new size_t(0);
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T>& x) { //uniq(x)
        if (*this->num_shared == 0) {
            this->num_shared = new size_t(*x.num_shared + 1);
            this->num_weak = x.num_weak;
            this->data = x.data;
        } else if (this->data != x.data) {
            if (*(this->num_shared) == 1) {
                delete this->data;
                delete this->num_shared;
                delete this->num_weak;
            } else {
                this->num_shared = new size_t(*this->num_shared - 1);
                this->data = x.data;
                this->num_shared = new size_t(*x.num_shared + 1);
                this->num_weak = x.num_weak;
            }
        }
    }

    template <typename T>
    shared_ptr<T> & shared_ptr<T>::operator=(const shared_ptr<T>& x) { //прилетает ссылка создаю новый объект
        if (this != &x && *this->num_weak == 1) {
            delete(this->data);
            delete(this->num_shared);
            delete(this->num_weak);
            this->data = x.data;
            this->num_shared = new size_t(*x.num_shared + 1);
            this->num_weak = x.num_weak;
            return *this;
        }
        if (this != &x) {
            this->data = x.data;
            this->num_shared = new size_t(*x.num_shared + 1);
            this->num_weak = x.num_weak;
        }
        return *this;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& x) {
        this->data = x.data;
        this->num_shared = new size_t(*x.num_shared + 1);
        this->num_weak = x.num_weak;
    }

    template <typename T>
    shared_ptr<T> & shared_ptr<T>::operator=(shared_ptr<T>&& x) { //прилетает напрямиую ссылка
        if (this != &x && *this->num_weak == 1) {
            delete(this->data);
            delete(this->num_shared);
            delete(this->num_weak);
            this->data = x->data;
            this->num_shared = x->num_shared;
            this->num_weak = x->num_weak;
            return *this;
        }
        if (this != &x) {
            this->data = x.data;
            this->num_shared = x.num_shared;
            this->num_weak = x.num_weak;
        }
        return *this;
    }

    template <typename T> 
    shared_ptr<T>::~shared_ptr() {
        if (*(this->num_shared) == 1) {
            delete this->data;
            delete this->num_shared;
            delete this->num_weak;
        }
    }

    template <typename T> 
    T &shared_ptr<T>::operator*() const {  
        return *this->data;
    }

    template <typename T>
    T *shared_ptr<T>::operator->() const {
        return this->data;
    }
}



class TestClass {
public:
    TestClass(int value) : value(value) {
        std::cout << "TestClass constructor: " << value << std::endl;
    }
    ~TestClass() {
        std::cout << "TestClass destructor: " << value << std::endl;
    }
    void display() const {
        std::cout << "Value: " << value << std::endl;
    }
private:
    int value;
};

void test_unique_ptr() {
    using namespace pointers;

    std::cout << "Testing unique_ptr..." << std::endl;

    unique_ptr<TestClass> ptr1(new TestClass(10));

    ptr1->display();

    (*ptr1).display();

    unique_ptr<TestClass> ptr2(std::move(ptr1));

    if (ptr1.operator->() == nullptr) {
        std::cout << "ptr1 is null after move." << std::endl;
    }

    ptr2->display();

    ptr2 = unique_ptr<TestClass>(new TestClass(20));
    ptr2->display();

    unique_ptr<TestClass> ptr3;
    ptr3 = std::move(ptr2);

    if (ptr2.operator->() == nullptr) {
        std::cout << "ptr2 is null after move assignment." << std::endl;
    }

    ptr3->display();

    std::cout << "Exiting test_unique_ptr function." << std::endl;
}

void test_shared_ptr() {
    using namespace pointers;

    std::cout << "Testing shared_ptr..." << std::endl;

    shared_ptr<TestClass> ptr1(new TestClass(100));

    shared_ptr<TestClass> ptr2(ptr1);

    ptr1->display();
    ptr2->display();
    shared_ptr<TestClass> ptr3;
    ptr3 = ptr1;

    ptr3->display();
    shared_ptr<TestClass> ptr4(std::move(ptr1));
    if (ptr1.operator->() == nullptr) {
        std::cout << "ptr1 is null after move." << std::endl;
    }

    ptr4->display();

    std::cout << "Exiting test_shared_ptr function." << std::endl;
}

int main() {
    test_unique_ptr();
    test_shared_ptr();
    return 0;
}
