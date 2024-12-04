/*
We are giving you guiding comments to help you fill out this header file.
The indentation of the comments serve as hints to how your code is structured. 

These are HINTS. PLEASE READ THE README.
Anything not specified here will be in the README.
For example, some functions may be const versions while others may not.
Some functions may throw exceptions while others are noexcept.
*/

/* Preprocessor directives. Guard the header file upon include */
#ifndef ICS_VECTOR_H
#define ICS_VECTOR_H
/*
Which include directives should you put here?
(hint: we may throw VectorExceptions. We also want to use ostream)
*/
#include "catch_amalgamated.hpp"
#include "vector_exception.hpp"

/*
Templated Vector class definition with templated Iterator class member
The template type name can be T
*/
template <class T>
class Vector {
/* Begin by specifying private members of Vector */
private:
    /* Write out the private members of Vector */
    size_t m_capacity;
    size_t m_size;
    T* m_data;
    /* We want to nest the Iterator class definition right here */
    class Iterator {
    /* Write out the private members of Iterator */
    private:
        /* there should be an m_container and an index */
        Vector *m_container;
        size_t m_index;
    /* Here are our your public members of Iterator*/
    public:
        /* Write your constructors here */
        Iterator(Vector* container, size_t index) noexcept : m_container(container), m_index(index) {
            // if (container == nullptr || m_index >= m_container->size() || m_index < 0) {
            //     m_index = 0;
            // }
            // std::cout << "L47 " << m_index << std::endl;
        }
        Iterator(const Iterator& other) noexcept : m_container(other.m_container), m_index(other.m_index) {}

        /* Write your operator overloads here.*/
        Iterator& operator=(const Iterator& other) noexcept {
            if (this != &other) {
                m_container = other.m_container;
                m_index = other.m_index;
            }
            return *this;
        }

        /* Post and pre increment and decrement operators*/
        Iterator & operator++() {
            if (m_index >= m_container->size()) {
                throw VectorException("out of bounds");
            }
            m_index++;
            return *this;
        }
        Iterator operator++(int) {
            if (m_index >= m_container->size()) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            m_index++;
            return temp;
        }
        Iterator & operator--() {
            if (m_index == 0) {
                throw VectorException("out of bounds");
            }
            m_index--;
            return *this;
        }
        Iterator operator--(int) {
            if (m_index == 0) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            m_index--;
            return temp;
        }

        /* Overloaded += size_t operator */
        // Iterator & operator+=(size_t offset) const {
        Iterator & operator+=(size_t offset) {
            if (m_index + offset >= m_container->size()) {
                throw VectorException("out of bounds");
            }
            m_index += offset;
            return *this;
        }

        /* Overloaded -= size_t operator */
        //Iterator & operator-=(size_t) const;
        Iterator & operator-=(size_t offset) {
            if (m_index < offset) {
                throw VectorException("out of bounds");
            }
            m_index -= offset;
            return *this;
        }


        /* Overloaded - operator. The right hand side is a const Iterator& */
        size_t operator-(const Iterator & other) const {
            if (m_container != other.m_container) {
                throw VectorException("iterators point to different containers");
            }
            return m_index - other.m_index;
        }

        /* Overloaded - operator.  The right hand side is a size_t */
        Iterator operator-(size_t offset) const {
            if (m_index < offset) {
                throw VectorException("out of bounds");
            }
            return Iterator(m_container, m_index - offset);
        }

        /* Overloaded == operator. The right hand side is a const Iterator& */
        bool operator==(const Iterator& other) const noexcept {
            if (m_container != other.m_container) { return false; }
            return m_index == other.m_index;
        }

        /* Overloaded != operator. The right hand side is const Iterator& */
        bool operator!=(const Iterator& other) const noexcept {
            return !(*this == other);
        }

        /* Overloaded star (*) operator to dereference. This returns a T& */
        T & operator*() {
            if (m_index >= m_container->size() || m_index < 0) {
                throw VectorException("out of bounds");
            }
            return m_container->m_data[m_index];
        }

        /* Overloaded -> operator. This returns a T* */
        const T * operator->() const {
            if (m_index >= m_container->size() || m_index < 0) {
                throw VectorException("out of bounds");
            }
            return &m_container->m_data[m_index];
        }

        /*
        It is correct to add a size_t to an Iterator.
        What keyword should you use to specify these next two overloads? (It's in the README)
        Remember, using + on Iterators is commutative.
        1 + Iterator and Iterator + 1 both return an Iterator that is one forward.
        */
        friend Iterator operator+(size_t offset, const Iterator & iter) {
            if (iter.m_index + offset >= iter.m_container->size()) {
                throw VectorException("out of bounds");
            }
            Iterator new_iter(iter);
            new_iter.m_index += offset;
            // new_iter += offset;
            return new_iter;
        }
        friend Iterator operator+(const Iterator & iter, size_t offset) {
            if (iter.m_index + offset >= iter.m_container->size()) {
                throw VectorException("out of bounds");
            }
            Iterator new_iter(iter);
            new_iter.m_index += offset;
            // new_iter += offset;
            return new_iter;
        }

        Vector * get_container() const {
            return m_container;
        }

        size_t get_index() const {
            return m_index;
        }
    };

    /* Specify your private Vector member fields. There should be three */


/* You will define your public Vector members here*/
    public:
    /* Default constructor */
    Vector() : m_capacity(0), m_size(0), m_data(nullptr) {}


    /* An overloaded constructor (see README) */
    Vector(size_t capacity) : m_capacity(capacity), m_size(0), m_data(new T[capacity]) {}

    /* The begin() function */
    Iterator begin() noexcept {
        return Iterator(this, 0);
    }


    /* The const version of begin(). Note: it returns a const T* type */
    T const * begin() const noexcept {
        if (m_data == nullptr) {
            return nullptr;
        }
        return m_data;
    }

    /* The empty() function */
    bool empty() const noexcept {
        return m_size == 0;
    }

    /* The end() function */
    Iterator end() noexcept {
        return Iterator(this, m_size);
    }

    /* The const version of end(). Note: it returns a const T* */
    T const * end() const noexcept {
        if (m_data == nullptr) {
            return nullptr;
        }
        return m_data + m_size;
    }

    /* The front() function */
    T & front() noexcept {
        if ((m_data == nullptr) || (m_size == 0)) {
            static T null_value;
            return null_value;
        }
        return m_data[0];
    }

    /* The const version of front(). Note it returns a const T& this is different from begin()! */
    T const & front() const noexcept {
        if ((m_data == nullptr) || (m_size == 0)) {
            static T null_value;
            return null_value;
        }
        return m_data[0];
    }

    /* The back() function */
    T & back() noexcept {
        if ((m_data == nullptr) || (m_size == 0)) {
            static T null_value;
            return null_value;
        }
        return m_data[m_size - 1];
    }

    /* The const version of back(). Note: it returns a const T& */
    T const & back() const noexcept {
        if ((m_data == nullptr) || (m_size == 0)) {
            static T null_value;
            return null_value;
        }
        return m_data[m_size - 1];
    }

    /* The push_back() function */
    void push_back(const T& val) {
        if (m_size == m_capacity) {
            // if the capacity is 0, set it to 1, otherwise double
            size_t new_capacity =  (m_capacity == 0 ? 1 : m_capacity << 1);
            T* new_data = new T[new_capacity]; 
            for (size_t i = 0; i < m_size; i++) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size] = val;
        m_size++;
    }

    /* The push_back function that takes an RValue reference (Type of T&&) */
    void push_back(T&& val) {
        if (m_size == m_capacity) {
            // if the capacity is 0, set it to 1, otherwise double
            size_t new_capacity =  (m_capacity == 0 ? 1 : m_capacity << 1);
            T* new_data = new T[new_capacity]; 
            for (size_t i = 0; i < m_size; i++) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size] = std::move(val);
        m_size++;
    }

    /* The pop_back() function*/
    void pop_back() {
        if (m_size == 0) {
            throw VectorException("popping from empty");
        }
        m_size--;
        m_data[m_size].~T();
    }

    /* The capacity() function */
    size_t capacity() const noexcept {
        return m_capacity;
    }

    /* The size() function */
    size_t size() const noexcept {
        return m_size;
    }

    /* The data() function. Returns type T* */
    T * data() noexcept {
        return m_data;
    }

    /* The const version of data(). Returns type const T* */
    T const * data() const noexcept {
        return m_data;
    }

    /* 
    The erase function. It takes in a start and end Iterator
    Hints for implementation:
        0 1 2 3 4 5
    We want to delete 1 2 3 
        0    1    2    3    4    5
             ^start         ^end
    Replace what is at start with what is at end and advance start and end until it reaches the vec.end()
        0    4    2    3    4    5
                  ^s             ^e
        0    4    5    3    4    5
                       ^s            e=vec.end()
    Is anything after what s is now including s used?
    Hint: resize the vector to include only 0 4 5. You will implement resize anyways.
    */
    void erase(Iterator & start, Iterator end) {
        if (start.get_container() != this || end.get_container() != this) {
            throw VectorException("Iterators do not belong to the same vector");
        }

        if (start.get_index() >= end.get_index()) {
            return; 
        }
        if (start.get_index() >= m_size || end.get_index() > m_size) {
            throw VectorException("out of bounds");
        }

        size_t move_steps = m_size - end.get_index();
        size_t del_cnt = end.get_index() - start.get_index();

        for (size_t i = 0; i < move_steps; i++) {
            m_data[start.get_index() + i] = std::move(m_data[end.get_index() + i]);
        }

        for (size_t i = 0; i < del_cnt; i++) {
            m_data[start.get_index() + move_steps + i].~T();
        }

        m_size -= del_cnt;
    }

    void erase(Iterator & start) {
        if (start.get_container() != this) {
            throw VectorException("Iterator does not belong to this vector");
        }
        if (start.get_index() >= m_size) {
            throw VectorException("out of bounds");
        }
        Iterator end(start);
        end++; 
        erase(start, end);
    }

    /* swap_elements(). Takes two iterators. Use std::move ! */
    void swap_elements(Iterator lhs, Iterator rhs) noexcept {
        if (lhs == rhs) {
            return;
        }

        T temp = std::move(*lhs);
        *lhs = std::move(*rhs);
        *rhs = std::move(temp);
    }

    /* Subscript operator[] overload */
    T & operator[](size_t index) noexcept {
        // if (index >= m_size || index < 0) {
        //     throw VectorException("out of bounds");
        // }
        return m_data[index];
    }


    /* Const version of the subscript operator[] overload */
    T const & operator[](size_t index) const noexcept {
        return m_data[index];
    }

    /* 
    Overloaded == operator. The right hand side is another const<T>& vector.
    Make sure the sizes of the vectors are equal
    Also check the elements inside are equal.
    */
    bool operator==(const Vector & other) const noexcept {
        if (m_size != other.m_size) {
            return false;
        }
        for (size_t i = 0; i < m_size; i++) {
            if (m_data[i] != other.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    /* Overloaded != operator. */
    bool operator!=(const Vector & other) const noexcept {
        return !(*this == other);
    }

    /* Vector copy constructor. Does a deep copy! */
    Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_data(nullptr) {
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = other.m_data[i];
    }

    /* 
    Vector assignment operator.
    Make sure you don't leak memory here. 
    */
    Vector& operator=(const Vector& other) {
        if (other.m_data == nullptr) {
            delete[] m_data;
            m_data = nullptr;
            m_capacity = 0;
            m_size = 0;
            return *this;
        }
        if (this != &other) {
            delete[] m_data;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++)
                m_data[i] = other.m_data[i];
        }
        return *this;
    }

    /* at() function. */
    T & at(size_t index) {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_data[index];
    }

    /* const version of at() */
    T const & at(size_t index) const {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_data[index];
    }

    /* 
    operator<< 
    We want to write code that can write Vectors to an output stream
    like std::cout << v << std::endl;
    You should use the friend keyword somewhere in here. 
    */
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec) {
        for (size_t i = 0; i < vec.m_size; i++) {
            out << vec.m_data[i];
            out << " "; 
        }
        return out;
    }

    /*
    Vector resize() function here.
    Allocate a new buffer to move all the old elements from the old one to.
    And then assign that new buffer to the `this`
    Make sure to use std::move() to move data from the old buffer to the new one.
    Make sure you don't leak memory!
    */
    void resize(size_t new_capacity){
        if (new_capacity <= 0) {
            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }
            delete[] m_data;
            m_data = nullptr;
            m_capacity = 0;
            m_size = 0;
            return;
        }

        if (new_capacity == m_capacity) {
            return;
        }
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < (m_size < new_capacity ? m_size : new_capacity); i++) {
            new_data[i] = std::move(m_data[i]);
        }
        for (size_t i = 0; i < m_size; i++) {
            m_data[i].~T();
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
        m_size = (m_size < new_capacity ? m_size : new_capacity);
    }

    /*
    clear() function. Make sure the destructor of each element gets called.
    delete[] will automatically do this. 
    But there other ways of implementing this function.
    */
    void clear() noexcept {
        for (size_t i = 0; i < m_size; i++) {
            m_data[i].~T();
        }
        m_size = 0;
    }

    /* Move constructor here */
    Vector(Vector&& other) noexcept : 
        m_capacity(other.m_capacity), m_size(other.m_size), m_data(std::move(other.m_data)) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    /* 
    Move assignment here
    Make sure there are not memory leaks!
    */
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        if (other.m_data == nullptr) {
            delete[] m_data;
            m_data = nullptr;
            m_capacity = 0;
            m_size = 0;
            return *this;
        }

        if (m_data) {
            delete[] m_data;
        }
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = std::move(other.m_data);
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        return *this;
    }


    /* The Vector destructor goes here. Make sure there are no leaks */
    ~Vector() {
        if (m_data != nullptr) {
            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }
            delete[] m_data;
        }
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

};
/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/
#endif
