#include "da.h"

template <class T>
DArray<T>::DArray()
{
    arr = new T[INC];
    size = INC;
    cont = 0;
}
template <class T>
DArray<T>::~DArray()
{
    delete[] arr;
}

template <class T>
size_t DArray<T>::csize()
{
    return size;
}

template <class T>
void DArray<T>::expand()
{
    int *newarr = new T[size + INC];
    for (size_t i = 0; i < cont; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = newarr;
    size = size + INC;
}

template <class T>
void DArray<T>::insert(T value)
{
    if (cont == size)
        expand();
    arr[cont] = value;
    cont++;
}
