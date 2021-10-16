#include "da.h"

DArray::DArray()
{
    arr = new int[INC];
    size = INC;
    cont = 0;
}

DArray::~DArray()
{
    delete[] arr;
}

void DArray::expand()
{
    int *newarr = new int[size + INC];
    for (size_t i = 0; i < cont; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = newarr;
    size = size + INC;
}

void DArray::insert(int value, bool back)
{
    if (cont == size)
        expand();
    
    if (back)
    {
        for (size_t i = cont; i > 0; i--)
        {
            arr[i] = arr[i - 1];
            arr[0] = value;
        }
    }
    else
        arr[cont] = value;
    cont++;
}
