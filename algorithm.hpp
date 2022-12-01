#ifndef SDMUTILS_SORTS_HPP
#define SDMUTILS_SORTS_HPP

namespace sdm
{
    template<typename T>
    constexpr void swap(T& first, T& second)
    {
        T temp = first;
        first = second;
        second = temp;
    }

	namespace sort
	{
		template<class Iter>
		constexpr void bubble(Iter begin, Iter end)
		{
			bool sure = true;
			while (sure)
			{
				sure = false;
				for (auto start = begin; start < end; ++start)
				{
					if (*start > *(start+1))
					{
						swap(*start,*(start+1));
						sure = true;
					}
				}
			}
		}
		template<class Iter>
		constexpr void insertion(Iter begin, Iter end)
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
}
#endif
