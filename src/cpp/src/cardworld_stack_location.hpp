
#ifndef CARDWORLD_STACK_LOCATION_HPP
#define CARDWORLD_STACK_LOCATION_HPP

#include <vector>

#include "cardworld.hpp"

class cardworld::stack_location {

	private:

		using container_type = std::vector < key_type >;
		using const_iterator = container_type::const_iterator;

		container_type _items;

	public:

		stack_location ( container_type const & items );
		stack_location ( container_type && items );

		const_iterator begin () const;
		const_iterator end () const;
};

#endif

