#include <iostream>
#include <array>
#include "movers.hpp"

int main()
{
    std::array<int,5> arr = { 5, 3, 2, 1, 9};
    for ( auto x : arr )
    { std::cout << x << std::endl; }
    std::cout << std::endl;
    sdm::sort(arr.begin(), arr.end());
    for ( auto x : arr )
    { std::cout << x << std::endl; }
    system("PAUSE");
}
