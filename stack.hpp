#ifndef SDMUTILS_STACK_HPP
#define SDMUTILS_STACK_HPP
namespace sdm
{
template<typename Type, int t_size = 10>
class stack
{
	Type m_Data[t_size];
	unsigned m_Top = 0;

	public:
	constexpr stack() { for (int i = 0; i < t_size; ++i) m_Data[i] = -1; }
	constexpr void push()
	{
		if (m_Top < t_size-1)
			++m_Top;
	}
	constexpr void push(const Type& payload)
	{
		if (m_Top < t_size-1)
		{
			setTop(payload);
			++m_Top;
		}
	}
	constexpr void pop()
	{
		if (m_Top > 0)
			--m_Top;
	}
	constexpr Type top()
	{ return m_Data[m_Top]; }
	constexpr void setTop(const Type& payload)
	{ m_Data[m_Top] = payload; }
	constexpr int maxSize()
	{ return t_size; }
	constexpr unsigned size()
	{ return m_Top; }
};
}
#endif
