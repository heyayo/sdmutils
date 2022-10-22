#ifndef SDMUTILS_ARRAY_HPP
#define SDMUTILS_ARRAY_HPP

#include "iterator.hpp"

namespace sdm
{
    template<typename Type, size_t fSize>
    class array
    {
    public:
        using TypeRef = Type&;
        using TypePtr = Type*;
        using Iter = Generic_Iterator<Type>;
        using IterRef = Iter&;
        using IterPtr = Iter*;

    public:

        constexpr TypeRef operator[](size_t index) { return data[index]; }
        constexpr TypeRef operator[](size_t index) const { return data[index]; }

        constexpr TypeRef at(size_t pos) { return data[pos]; }
        constexpr size_t Size()
        { return fSize;}
        constexpr Iter begin()
        { return Iter(data); }
        constexpr Iter end()
        { return Iter(data + fSize); }

        constexpr friend std::ostream& operator<<(std::ostream& stream, const array& other)
        { for ( int x = 0; x < fSize; ++x ) { stream << x;} return stream; }

        Type data[fSize];
    };
}

#endif //SDMUTILS_ARRAY_HPP
