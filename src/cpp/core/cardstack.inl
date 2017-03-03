
#include <algorithm>

template < typename Rng >
auto cardstack::shuffle ( Rng && rng ) -> this_type & 
{
	std::shuffle ( _order.begin() , _order.end() , rng );
	return *this;
}

