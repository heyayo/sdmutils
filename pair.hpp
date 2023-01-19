#ifndef SDMUTILS_PAIR_HPP
#define SDMUTILS_PAIR_HPP

namespace sdm
{
	template<typename t_Left,typename t_Right>
	class pair
	{
		public:
		t_Left left;
		t_Right right;
	};
}
#endif
