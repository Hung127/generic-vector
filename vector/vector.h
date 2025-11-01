#ifndef _LIB_VECTOR_H_
#define _LIB_VECTOR_H_

#include <expected>
#include <iostream>
#include <string>
using std::cout, std::cin, std::ostream, std::istream;
using std::expected;
using std::string;
using std::unexpected;

namespace lib {
template <class T>
class vector {
private:
    T* _arr;
    int _capacity;
    int _size;
    static constexpr int EXPAND_TIMES = 2;

public:
    // constructors / destructor
    vector();
    explicit vector(int capacity);
    vector(const vector& other);
    ~vector();

    // modifiers / observers
    void push_back(const T& value);  // NOLINT
    [[nodiscard]] int size() const;

    // bounds-checked read operator returning an expected
    std::expected<T, std::string> operator[](int idx) const;

    vector& operator=(const vector& other);
};
}  // namespace lib

// Default ctor
template <class T>
lib::vector<T>::vector() : _arr(new T[1]), _capacity(1), _size(0) {}

// Constructor with initial capacity (if capacity <= 0, use 1)
template <class T>
lib::vector<T>::vector(int capacity)
    : _arr(new T[(capacity > 0) ? capacity : 1]),
      _capacity((capacity > 0) ? capacity : 1),
      _size(0) {}

// Copy constructor
template <class T>
lib::vector<T>::vector(const vector& other)
    : _arr(new T[other._capacity]), _capacity(other._capacity), _size(other._size) {
    std::copy(other._arr, other._arr + other._size, _arr);
}

// Destructor
template <class T>
lib::vector<T>::~vector() {
    delete[] _arr;
    // cout << "Array deleted\n";
}

// push_back (reallocates when necessary)
template <class T>
void lib::vector<T>::push_back(const T& value) {
    if (_size == _capacity) {
        int newCap = _capacity * EXPAND_TIMES;
        T* newArr = new T[newCap];
        std::copy(_arr, _arr + _size, newArr);
        delete[] _arr;
        _arr = newArr;
        _capacity = newCap;
    }
    _arr[_size] = value;  // NOLINT
    _size++;
}

// size accessor
template <class T>
int lib::vector<T>::size() const {
    return _size;
}

// bounds-checked operator[]
template <class T>
std::expected<T, std::string> lib::vector<T>::operator[](int idx) const {
    if ((idx < 0) || (idx >= _size)) {
        return std::unexpected<std::string>("Out of range");
    }
    return _arr[idx];
}

template <class T>
lib::vector<T>& lib::vector<T>::operator=(const lib::vector<T>& other) {
    if (this == &other) {
        return *this;
    }
    other[0];
    return *this;
}

#endif  // !_LIB_VECTOR_H_
