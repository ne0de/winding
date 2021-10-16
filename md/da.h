#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

template <class T>
class DArray
{
private:
    T *arr;
    size_t size;
    size_t cont;
    const static size_t INC = 1;

    void expand();

public:
    DArray();
    ~DArray();

    void insert(T value);
    inline size_t csize();

    T operator[](size_t position)
    {
        return arr[position];
    }
};

#include "da.hxx"

#endif
