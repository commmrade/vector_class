
#include <cstddef>
#include <stdexcept>
#include<vector>


template<typename T> 
concept Element = requires(T a) {
    std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>;
};

template<typename Element>
class Vector 
{
private:
    Element *ptr;
    using value_type = Element;


    size_t sz;
    size_t cap;
public:
    
    Vector() 
    {
        ptr = new value_type[5];
        cap = 5;
        sz = 0;
    }
    explicit Vector(size_t size)
    {
        if (size > 0) {
            ptr = new value_type[size + 5];
            this->sz = size;
            cap = size * 2;
        } else {
            ptr = new value_type[8];
            sz = 0;
            cap = 8;
        }
    }
    explicit Vector(std::initializer_list<value_type> list) {
        ptr = new value_type[list.size() * 2];
        sz = list.size();
        cap = sz * 2;

        std::copy(list.begin(), list.end(), ptr);
    }

    class Iterator;
    class Const_Iterator;

    inline size_t size() const { return sz; }
    inline size_t capacity() const { return cap; }

    //Change methods
    void push_back(const value_type &value)
    {
        if (sz < cap) 
        {
            ptr[sz] = value;
            sz++;
        } 
        else
        {
            value_type* temp_ptr = new value_type[sz * 2];
            memcpy(temp_ptr, ptr, sz * sizeof(value_type)); //copying old elements
            temp_ptr[sz] = value;

            sz++;
            cap *= 2; //Updating size and capacity

            delete []ptr;
            ptr = temp_ptr;
        }
        //std::cout << size << " " << capacity << std::endl;
    }

    void pop_back() {
        ptr[sz - 1] = NULL;
        sz--;
    }

    void erase(const size_t index) {
        
        if (index >= sz) {
            throw std::runtime_error("Out of bounds");
        }
        value_type* temp_ptr = new value_type[cap];

        memcpy(temp_ptr, ptr, index * sizeof(value_type)); //Copiying part before the erased number
        
        memcpy(temp_ptr + index, ptr + index + 1, (sz - index) * sizeof(value_type)); //Copying everything after inserted number
        sz--;
        
        delete []ptr;
        ptr = temp_ptr;
    }

    void insert(const size_t index, const value_type& value) {

        if (index > sz) {
            throw std::runtime_error("Out of bounds");
        }
        
        if (sz + 1 > cap) { 
            
            reserve(cap * 2);
            
            
        } //Reserving more space

        for (size_t i = sz; i > index; i--) {
            ptr[i] = ptr[i - 1];
        } //Shifting elements
    
        ptr[index] = value;
        sz++; 
    }
    void insert(const Const_Iterator &iter, const value_type& value) {
        int index = iter - cbegin();

        if (index > sz) {
            throw std::runtime_error("Out of bounds");
        }
        
        if (sz + 1 > cap) { 
            
            reserve(cap * 2);
            
            
        } //Reserving more space

        for (size_t i = sz; i > index; i--) {
            ptr[i] = ptr[i - 1];
        } //Shifting elements
    
        ptr[index] = value;
        sz++; 
        
    }

    void reserve(int new_capacity) {
        value_type* temp_ptr = new value_type[new_capacity];
        this->cap = new_capacity;

        memcpy(temp_ptr, ptr, sz * sizeof(value_type));

        delete []ptr;
        ptr = temp_ptr;
    }


    void resize(int new_size) {
        sz = new_size;

        value_type* temp_ptr = new value_type[cap];
        memcpy(temp_ptr, ptr, new_size * sizeof(value_type));

        delete []ptr;
        
        ptr = temp_ptr;
        
    }


    //Access methods

    value_type& operator[](const size_t index) {
        if (index < sz) {
            return ptr[index];
        } else {
            throw std::runtime_error("Out of bounds");
        }
    }

    value_type& at(const size_t index) {
        if (index < sz) {
            return ptr[index];
        } else {
            throw std::runtime_error("Out of bounds");
        }
    }
    value_type at(const Iterator &iterator) {
        return *iterator;
    }
    value_type& at(const Const_Iterator &iterator) {
        return *iterator;
    }

    inline value_type front() const {
        return ptr[0];
    }
    inline value_type back() const {
        return ptr[sz - 1];
    }
    //Iterator field
    class Iterator {
    private:
        value_type* ptr_it;
    public:
        

        Iterator(value_type* ptr_pass) {
            ptr_it = ptr_pass;
        }

        value_type& operator*() {
            return *ptr_it;
        }
        const value_type& operator*() const {
            return *ptr_it;
        }
        Iterator& operator++() {
            ptr_it++;
            return *this;
        }
        Iterator& operator++(int) {
            ptr_it++;
            return *this;
        }
        bool operator==(const Iterator &other) {
            return ptr_it == other.ptr_it;
        }
        bool operator!=(const Iterator &other) {
            return !(ptr_it == other.ptr_it);
        }
    };

    Iterator begin() {
        return Iterator(ptr);
    }
    Iterator end() {
        return Iterator(ptr + sz);
    }

    class Const_Iterator {
    private:
        value_type* ptr_it;
    public:
        

        Const_Iterator(value_type* ptr_pass) {
            ptr_it = ptr_pass;
        }

        const value_type& operator*() const {
            return *ptr_it;
        }
        Const_Iterator& operator++() {
            ptr_it++;
            return *this;
        }
        Const_Iterator& operator++(int) {
            ptr_it++;
            return *this;
        }
        Const_Iterator operator+(const int steps) {
            return Const_Iterator(ptr_it + steps);
        }


        bool operator==(const Const_Iterator &other) {
            return ptr_it == other.ptr_it;
        }
        bool operator!=(const Const_Iterator &other) {
            return !(ptr_it == other.ptr_it);
        }

        std::ptrdiff_t operator-(const Const_Iterator &other) const {
            return ptr_it - other.ptr_it;
        }
    };
    Const_Iterator cbegin() {
        return Const_Iterator(ptr);
    }
    Const_Iterator cend() {
        return Const_Iterator(ptr + sz);
    }

};
