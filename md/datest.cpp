#include <iostream>
#include "da.h"

using namespace std;

int main(int argc, char const *argv[])
{
    DArray<int> arr;

    arr.insert(10);
    arr.insert(10);
    arr.insert(1150);

    for (size_t i = 0; i < arr.csize(); i++)
        cout << arr[i] << " ";

    return 0;
}
