#include <iostream>
#include "lde.h"

int main(int argc, char const *argv[])
{
    lde<int> container;

    container <= 1 <= 2;
    container << 3 << 4;

    std::cout << container.size() << std::endl;
    return 0;
}
