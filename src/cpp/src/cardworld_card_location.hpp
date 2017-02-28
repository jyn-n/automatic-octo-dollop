
#ifndef CARDWORLD_CARD_LOCATION_HPP
#define CARDWORLD_CARD_LOCATION_HPP

#include "cardworld_stack_location.hpp"
#include "cardworld.hpp"

class cardworld::card_location {

	private:

		stack_location _stack;
		key_type _card;

	public:

		card_location ( stack_location const & stack , key_type const & card );

		stack_location const & stack () const;
		key_type const & card () const;
};

#endif

