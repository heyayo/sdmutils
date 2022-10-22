#ifndef SDMUTILS_ARRAY_HPP
#define SDMUTILS_ARRAY_HPP

namespace sdm
{
    template<typename type, int size>
    class arrayIterator
    {
        type* ptr;

    public:
        using iter = arrayIterator;
        using iterRef = arrayIterator&;
        using iterPtr = arrayIterator*;
        using typeRef = type&;
        using typePtr = type*;

    public:
        arrayIterator(type* nptr) : ptr(nptr) {};
        
        iterRef operator++()
        { ptr++; return *this; }
        iter operator++(int)
        { iter temp = *this; ++(*this); return temp; }

        iterRef operator--()
        { ptr--; return *this; }
        iter operator--(int)
        { iter temp = *this; --(*this); return temp; }

        typeRef operator[](int index)
        { return *(ptr + index); }

    };

    template<typename type, int size>
    class array
    {
        type data[size];
        unsigned maxSize = size;

    public:
        using typeRef = type&;
        using typePtr = type*;
        using iterator = arrayIterator;
        using iterRef = arrayIterator&;
        using iterPtr = arrayIterator*;

    public:

        typeRef operator[] (int index) { return data[index]; }

        typeRef at(int pos) { return data[pos] };

    };
}

#endif //SDMUTILS_ARRAY_HPP
