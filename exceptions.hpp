#include <exception>

namespace sdm
{
	class DivideByZero : public std::exception
	{
		const char* what() { return "Divide By Zero"; }
	};
}

