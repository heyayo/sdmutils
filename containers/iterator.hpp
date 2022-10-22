#ifndef SDMUTILS_ITERATOR_HPP
#define SDMUTILS_ITERATOR_HPP

namespace sdm
{
    template<typename Type>
    class Generic_Iterator
    {
        public:
        using Reference = Type&;
        using Pointer = Type*;
        using Iterator_Reference = Generic_Iterator&;
        using Iterator_Pointer = Generic_Iterator*;

        Pointer mPtr;

        public:
        Generic_Iterator(Pointer ptr) : mPtr(ptr) {}

        constexpr Iterator_Reference operator++()
        { ++mPtr; return *this; }
        constexpr Iterator_Reference operator++(int)
        { Generic_Iterator temp = *this; ++(*this); return temp; }
        constexpr Iterator_Reference operator--()
        { --mPtr; return *this; }
        constexpr Iterator_Reference operator--(int)
        { Generic_Iterator temp = *this; --(*this); return temp; }
        constexpr Iterator_Reference operator+=(const int diff)
        { mPtr += diff; return *this; }
        constexpr Iterator_Reference operator-=(const int diff)
        { mPtr -= diff; return *this; }
        constexpr Generic_Iterator operator+(const int& diff)
        { Generic_Iterator temp = *this; return temp += diff; }
        constexpr Generic_Iterator operator-(const int& diff)
        { Generic_Iterator temp = *this; return temp -= diff; }
        constexpr Reference operator*()
        { return *mPtr; }
        constexpr Pointer operator->()
        { return mPtr; }
        constexpr Reference operator[](int index)
        { return *(mPtr + index); }
        constexpr bool operator<(const Iterator_Reference other) const
        { return mPtr < other.mPtr; }
        constexpr bool operator>(const Iterator_Reference other) const
        { return mPtr > other.mPtr; }
        constexpr bool operator==(const Iterator_Reference other) const
        { return mPtr == other.mPtr; }
        constexpr bool operator!=(const Iterator_Reference other) const
        { return mPtr != other.mPtr; }
    };
}

#endif