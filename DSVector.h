///DSVector header file
///Created by Kenny Zhang
/// - "Mind the jank"

#ifndef INC_21F_PA02_DSSVECTOR_H
#define INC_21F_PA02_DSSVECTOR_H

#include <iostream>
#include <ostream>
#include <istream>

//Namespace declarations
using std::ostream;
using std::cout;
using std::endl;

template <typename t> class DSVector {

private:
    int size{}; //number of elements currently being used
    int capacity{}; //number of total possible elements that could be stored
    t* data; //head pointer of vector
    t* iterator = data; //function iterator

public:
    //Constructors
    DSVector();
    DSVector(int len, t val);
    DSVector(int size, int capacity, t* data);
    DSVector(const DSVector<t>& arg);
    ~DSVector();

    //Operators
    DSVector<t>& operator=(const DSVector<t>& arg);
    t& operator[](int index);
    friend ostream& operator<<(ostream& os, DSVector<t>& vect) {
        os << "[";
        for(int i = 0; i < vect.size; i++) {
            if (i != vect.size - 1) {
                os << vect.data[i] << ",";
            } else {
                os << vect.data[i];
            }
        }
        os << "]";

        return os;
    }

    //Vector Element Modifiers
    DSVector<t>& push_back(t val);
    void pop (int index);

    //Display Functions
    void print();

    //Size Modifier Functions
    void resize();

    //Comparison Functions
    bool compare (const t* arr, int arrSize);
    bool compare (const DSVector<t>& arg);

    //Get Functions
    int getSize();
    int getCapacity();
    t* getData();
    t getLast();

    //Iterator Functions
    t* begin();
    t* end();
    void increment_iterator();
    void decrement_iterator();
    t* get_iterator();
    t* get_next();
    bool has_next();
    void reset_iterator();

};

//Constructors:
/**
 * Default constructor.
 * Creates empty vector with a capacity of 10.
 * @tparam t
 */
template <typename t>
DSVector<t>::DSVector() {
    size = 0;
    capacity = 10;
    data = new t[capacity];
    iterator = data;
}

/**
 * Creates vector of size "len".
 * Capacity is set to 10 + "len".
 * All elements data is set to "val"
 * @tparam t
 * @param len - vector size
 * @param val - element value
 */
template <typename t>
DSVector<t>::DSVector(int len, t val) {
    size = len;
    capacity = len + 10;
    data = new t[capacity];
    iterator = data;

    for (int i = 0; i < size; i++) {
        data[i] = val;
    }
}

/**
 * Sets all vector members to their respective inputs.
 * @tparam t
 * @param size
 * @param capacity
 * @param data - vector head pointer
 */
template <typename t>
DSVector<t>::DSVector(int size, int capacity, t* data) {
    this->size = size;
    this->capacity = capacity;
    this->data = data;
    iterator = data;
}

/**
 * Copies "arg" to this vector
 * @tparam t
 * @param arg - argument copied
 */
template <typename t>
DSVector<t>::DSVector(const DSVector<t>& arg) {
    size = arg.size;
    capacity = arg.capacity;

    data = new t[capacity];
    iterator = data;
    for(int i = 0; i < size; i++)
        data[i] = arg.data[i];

}

/**
 * Deletes pointer array.
 * @tparam t
 */
template <typename t>
DSVector<t>::~DSVector() {
    delete [] data;
}

//Operators
/**
 * Sets this to "arg"
 * @tparam t
 * @param arg - argument copied
 * @return
 */
template <typename t>
DSVector<t>& DSVector<t>::operator=(const DSVector<t>& arg) {
    if (&arg != this) {
        delete[] data;
        this->size = arg.size;
        this->capacity = arg.capacity;
        this->data = new t[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = arg.data[i];
        }
    }
    return *this;
}

/**
 * Retrieves element at "index"
 * @tparam t
 * @param index
 * @return
 */
template<typename t>
t& DSVector<t>::operator[](int index) {
    return data[index];
}

//Vector Element Modifiers
/**
 * Adds new element to vector. If vector is at capacity, vector is resized.
 * @tparam t
 * @param val
 * @return
 */
template <typename t>
DSVector<t>& DSVector<t>::push_back(t val) {
    if (size >= capacity) {
        resize();
    }
    data[size] = val;
    size++;
}

/**
 * Deletes value at index and moves all elements afterwards forward one index
 * @tparam t
 * @param index
 */
template<typename t>
void DSVector<t>::pop (int index) {
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

//Display Functions
/**
 * Prints all vector elements to terminal
 * @tparam t
 * @note This is a debug function
 */
template<typename t>
void DSVector<t>::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

//Size Modifer Functions
/**
 * Resizes the vector to twice the capacity.
 * @tparam t
 */
template <typename t>
void DSVector<t>::resize() {
    t* temp = new t[capacity * 2];
    std::copy(begin(), end(), temp);
    delete[] data;
    data = temp;
    capacity = capacity * 2;
}

//Comparison Functions:
/**
 * Compares only checks the first "arrSize" elements of this->data and "arr"
 * @tparam t
 * @param arr - array this vector is compared to
 * @param arrSize - amount of elements compared
 * @return - true if elements are equal
 * @return - false if otherwise
 */
template<typename t>
bool DSVector<t>::compare (const t* arr, int arrSize){
    for(int i = 0; i < arrSize; i++) {
        if (arr[i] != data[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Compares to check if both vectors have the same elements
 * @tparam t
 * @param arg - vector to be compared
 * @return - true if vectors are the same
 */
template<typename t>
bool DSVector<t>::compare (const DSVector<t>& arg){
    for(int i = 0; i < arg.size; i++) {
        if (arg.data[i] != data[i]) {
            return false;
        }
    }
    return true;
}

//Get Functions:
/**
 * Gets size of vector
 * @tparam t
 * @return
 */
template <typename t>
int DSVector<t>::getSize() { return size; }

/**
 * Gets capacity of vector
 * @tparam t
 * @return
 */
template <typename t>
int DSVector<t>::getCapacity() { return capacity; }

/**
 * Gets data of vector
 * @tparam t
 * @return
 */
template <typename t>
t* DSVector<t>::getData() { return data; }

/**
 * Gets the last pointer of a vector
 * @tparam t
 * @return
 */
template<typename t>
t DSVector<t>::getLast() { return data[size - 1]; }

//Iterator Functions:
/**
 * Resets iterator to be equal to the head iterator
 * @tparam t
 */
template<typename t>
void DSVector<t>::reset_iterator() { iterator = data; }

/**
 * Returns iterator pointer
 * @tparam t
 * @return
 */
template<typename t>
t *DSVector<t>::get_iterator() { return iterator; }

/**
 * Returns pointer ahead of iterator
 * @tparam t
 * @return
 * @note There are no bounds checks
 */
template<typename t>
t* DSVector<t>::get_next() { return iterator + 1; }

/**
 * Moves iterator forward by one pointer.
 * @tparam t
 * @return
 * @note There are no bounds checks
 */
template<typename t>
void DSVector<t>::increment_iterator() { iterator++; }

/**
 * Moves iterator backwards by one pointer.
 * @tparam t
 * @return
 * @note There are no bounds checks
 */
template<typename t>
void DSVector<t>::decrement_iterator() { iterator--; }

/**
 * Returns the head pointer
 * @tparam t
 * @return
 */
template<typename t>
t* DSVector<t>::begin() { return data; }

/**
 * Returns the last element's pointer
 * @tparam t
 * @return
 */
template<typename t>
t* DSVector<t>::end() { return data + size; }

/**
 * Checks if the pointer after the iterator is a vector element
 * @tparam t
 * @return
 */
template<typename t>
bool DSVector<t>::has_next() {
    if (iterator < end()) {
        return true;
    } else {
        return false;
    }
}

#endif //INC_21F_PA02_DSSVECTOR_H
