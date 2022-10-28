#ifndef SDMUTILS_ARRAY_HPP
#define SDMUTILS_ARRAY_HPP

#include "iterator.hpp"
#include <iostream>

namespace sdm
{
    template<typename Type, int fSize>
    class array
    {
    public:
        using TypeRef = Type&;
        using TypePtr = Type*;
        using Iter = Generic_Iterator<Type>;
        using IterRef = Iter&;
        using IterPtr = Iter*;

    public:

        TypeRef operator[](const int index) { return data[index]; }
        //constexpr TypeRef operator[](const int index) const { return data[index]; }

        constexpr Type at(int pos) { return data[pos]; }
        constexpr int Size() const
        { return fSize;}
        constexpr Iter begin() const
        { return {data}; }
        constexpr Iter end() const
        { return Iter(data + fSize); }

        constexpr friend std::ostream& operator<<(std::ostream& stream, const array& other)
        { for ( int x = 0; x < fSize; ++x ) { stream << x;} return stream; }

        Type data[fSize];
    };
}

#endif //SDMUTILS_ARRAY_HPP
