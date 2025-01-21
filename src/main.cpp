#include <iostream>
#include "vec.h"

int main()
{

    Benchstl::vector<int, std::allocator<int>> test(10, std::allocator<int>());

    test.set(0, 4);

    std::cout << test.at(4) << '\n';
    return 0;
}