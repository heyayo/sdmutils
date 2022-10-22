#ifndef SDMUTILS_ITERATOR_HPP
#define SDMUTILS_ITERATOR_HPP

namespace sdm
{
    template<typename Type>
    class Iterator
    {
        public:
        using Reference = Type&;
        using Pointer = Type*;
        using Iterator_Reference = Iterator&;
        using Iterator_Pointer = Iterator*;

        private:
        Pointer mPtr;

        public:
        Iterator_Reference operator++()
        { ++mPtr; return *this; }
        Iterator_Reference operator++(int)
        { Iterator temp = *this; ++(*this); return temp; }
        Iterator_Reference operator--()
        { --mPtr; return *this; }
        Iterator_Reference operator--(int)
        { Iterator temp = *this; --(*this); return temp; }
        Iterator_Reference operator+=(const int diff)
        { mPtr += diff; return *this; }
        Iterator_Reference operator-=(const int diff)
        { mPtr -= diff; return *this; }
        Iterator operator+(const int diff)
        { Iterator temp = *this; return temp += diff; }
        Iterator operator-(const int diff)
        { Iterator temp = *this; return temp -= diff; }
        Reference operator*()
        { return *mPtr; }
        Pointer operator->()
        { return mPtr; }
        Reference operator[](int index)
        { return *(mPtr + index); }
        bool operator<(const Iterator_Reference other)
        { return mPtr < other.mPtr; }
        bool operator>(const Iterator_Reference other)
        { return mPtr > other.mPtr; }
        bool operator==(const Iterator_Reference other)
        { return mPtr == other.mPtr; }
        bool operator!=(const Iterator_Reference other)
        { return mPtr != other.mPtr; }
    };
}

#endif