#ifndef SDMUTILS_MATH_HPP
#define SDMUTILS_MATH_HPP
namespace sdm
{
	constexpr float EPSILON = 0.00001f;

	constexpr double root(double num)
	{
		constexpr double error = 1 * 10e-5;
		double s = num;
	
		while (s - num / s > error)
		{
			s = (s + num / s) / 2;
		}
		return s;
	}
	constexpr bool fEqual(float a, float b)
	{ return a - b <= EPSILON && b - a <= EPSILON; }
	template<typename Type>
	constexpr Type max(const Type& a, const Type& b)
	{ return a > b ? a : b; }
	template<typename Type>
	constexpr Type min(const Type& a, const Type& b)
	{ return a > b ? b : a; }
	template<typename Type>
	constexpr void lean(const Type& target, Type& ref, const Type& rate)
	{
		ref = max(min(ref + rate, target),ref - rate);
	}
}
#endif
