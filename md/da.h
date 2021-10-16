#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

class DArray
{
private:
    int *arr;
    size_t size;
    size_t cont;
    const static size_t INC = 5;

    void expand();

public:
    DArray();
    ~DArray();

    void insert(int value, bool back);
};

#endif
