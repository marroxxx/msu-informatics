#include "Pointers.hpp"
#include <vector>
#include <iostream>
#include <mutex>

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
        this->num_weak = new size_t(0);
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
            this->num_shared = x.num_shared;
            ++(*x.num_shared);
            this->num_weak = x.num_weak;
            this->data = x.data;
        } else if (this->data != x.data) {
            if (*(this->num_shared) == 1) {
                delete this->data;
                delete this->num_shared;
                delete this->num_weak;
                this->data = x.data;
                this->num_shared = x.num_shared;
                ++(*x.num_shared);
                this->num_weak = x.num_weak;
            } else {
                --this->num_shared;
                this->num_shared = x.num_shared;
                ++(*x.num_shared);
                this->data = x.data;
                this->num_weak = x.num_weak;
            }
        }
    }

    template <typename T>
    shared_ptr<T> & shared_ptr<T>::operator=(const shared_ptr<T>& x) { //прилетает ссылка создаю новый объект
        if (this != &x && *this->num_shared == 1) {
            delete(this->data);
            delete(this->num_shared);
            delete(this->num_weak);
            this->data = x.data;
            this->num_shared = x.num_shared;
            ++(*x.num_shared);
            this->num_weak = x.num_weak;
            return *this;
        }
        if (this != &x) {
            if (this->num_shared != 0) {
                --this->num_shared;
            }
            this->data = x.data;
            this->num_shared = x.num_shared;
            ++(*x.num_shared);
            this->num_weak = x.num_weak;
        }
        return *this;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& x) {
        this->data = x.data;
        this->num_shared = x.num_shared;
        this->num_weak = x.num_weak;
    }

    template <typename T>
    shared_ptr<T> & shared_ptr<T>::operator=(shared_ptr<T>&& x) { //прилетает напрямиую ссылка
        if (this != &x && *this->num_weak == 1) {
            delete(this->data);
            delete(this->num_shared);
            delete(this->num_weak);
            this->data = x.data;
            this->num_shared = x.num_shared;
            this->num_weak = x.num_weak;
            return *this;
        }
        if (this != &x) {
            if (this->num_shared != 0) {
                --this->num_shared;
            }
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

    template <typename T>
    weak_ptr<T>::weak_ptr(const weak_ptr<T>& x) {
        this->data = x.data;
        this->num_shared = x.num_shared;
        this->num_weak = x.num_weak;
        ++(*x.num_weak);
    }

    template <typename T>
    weak_ptr<T> & weak_ptr<T>::operator=(const weak_ptr<T>& x) { 
        if (this != &x) {
            this->data = x.data;
            this->num_shared = x.num_shared;
            this->num_weak = x.num_weak;
            ++(*x.num_weak);
        }
        return *this;
    }

    template <typename T>
    weak_ptr<T>::weak_ptr(const shared_ptr<T>& x) {
        this->data = x.data;
        this->num_shared = x.num_shared;
        this->num_weak = ++x.num_weak;
    }

    template <typename T>
    weak_ptr<T> & weak_ptr<T>::operator=(const shared_ptr<T>& x) {
        this->data = x.data;
        this->num_shared = x.num_shared;
        this->num_weak = ++x.num_weak;
        return *this;
    }

    template <typename T>
    weak_ptr<T>::weak_ptr(weak_ptr<T>&& x) {
        this->data = x.data;
        this->num_shared = x.num_shared;
        this->num_weak = x.num_weak;
    }

    template <typename T>
    weak_ptr<T> & weak_ptr<T>::operator=(weak_ptr<T>&& x) {
        if (this != &x) {
            this->data = x.data;
            this->num_shared = x.num_shared;
            this->num_weak = x.num_weak;
        }
        return *this;
    }

    template <typename T>
    weak_ptr<T>::~weak_ptr() {
        delete this->data;
        delete this->num_shared;
        delete this->num_weak;
    }

    template <typename T> 
    bool weak_ptr<T>::expired() {
        if (this->num_shared == nullptr || this->num_shared == 0) {
            return true;
        }
        return false;
    }

    template <typename T>
    T &weak_ptr<T>::operator*() {
        return *this->data;
    }

    template <typename T>
    T *weak_ptr<T>::operator->() {
        return this->data;
    }
}

class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& get_instance() {
        std::call_once(init_instance_flag, &Singleton::init_instance);
        return *instance;
    }

    void some_method() { 
        std::cout << "Вызван метод some_method" << std::endl;
    }

private:
    Singleton() {
        std::cout << "Создан экземпляр Singleton." << std::endl;
    }

    ~Singleton() {
        std::cout << "Уничтожен экземпляр Singleton." << std::endl;
    }
    static void init_instance() {
        instance = new Singleton();
    }

    static Singleton* instance;
    static std::once_flag init_instance_flag; 
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::init_instance_flag;

int main() {
    Singleton::get_instance().some_method();
    return 0;
}
