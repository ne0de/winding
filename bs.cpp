#include <iostream>

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T, size_t N>
void bubbleSort(T (&arr)[N])
{
    for (size_t i = N - 1; i > 0; i--)
        for (size_t j = 0; j < i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

int main(int argc, char const *argv[])
{
    // int arr[] = {-4, 4, -4, 10, -8, 3};
    float arr[] = {3.4, -6.3, 4};
    bubbleSort(arr);
    return 0;
}
