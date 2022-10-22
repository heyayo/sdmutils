#ifndef SDMUTILS_SORTS_HPP
#define SDMUTILS_SORTS_HPP

namespace sdm
{
    template<typename T>
    inline void swap(T& first, T& second)
    {
        T temp = first;
        first = second;
        second = temp;
    }

    template<class Iter>
    inline void sort(Iter begin, Iter end)
    {
        auto nend = end - 1;
        for (auto start = begin; start != nend; ++start)
        {
            if (*start > *(start+1))
            {
                //std::swap(start, start+1);
                swap(*start,*(start+1));
                if ( start == begin )
                    continue;
                start -= 2;
            }
        }
    }
}

// 1 1 2 3 3 4 5
// 4 5 1 3
// 5 3 2 1 9

#endif