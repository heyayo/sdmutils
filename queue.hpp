#ifndef SDMUTILS_QUEUE_HPP
#define SDMUTILS_QUEUE_HPP
/*

SDMUTILS - Queue

Circular Fixed Sized Array Based Queue

*/
#include <iostream>
namespace sdm
{
template<typename Type, int size>
class queue
{
	Type data[size];
	unsigned m_START = 0;
	unsigned m_END = 0;
	unsigned m_CAPACITY = size;

	public:
	constexpr bool enqueue(const Type& payload)
	{
		if (m_CAPACITY == 0)
			return false;
		data[m_END] = payload;
		if (++m_END >= size)
			m_END = 0;
		--m_CAPACITY;
		return true;
	}
	constexpr Type poll() // TODO | Return Type to Bool for proper termination , Extract Polled Value via Reference Parameter
	{
		if (m_CAPACITY >= size)
			return 0;
		auto temp = data[m_START];
		if (++m_START >= size)
			m_START = 0;
		++m_CAPACITY;
		return temp;
	}
	constexpr bool isEmpty()
	{ return m_CAPACITY >= size; }
	constexpr friend std::ostream& operator<<(std::ostream& stream, queue& other)
	{
		while (!other.isEmpty())
			stream << other.poll() << ' ';
		return stream;
	}
	constexpr void DEBUGSTATUS() // Temporary
	{
		std::cout << "DEBUG: " <<  m_START << ' ' << m_END << ' ' << m_CAPACITY <<  std::endl;
	}
};
}
#endif
