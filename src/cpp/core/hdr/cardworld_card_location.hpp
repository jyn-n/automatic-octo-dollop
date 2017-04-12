
#ifndef CARDWORLD_CARD_LOCATION_HPP
#define CARDWORLD_CARD_LOCATION_HPP

#include "cardworld_stack_location.hpp"
#include "cardworld.hpp"

namespace core {

template < typename T , typename >
class cardworld::card_location {

	public:

		using card_reference_type = T;

	private:

		stack_location _stack;
		card_reference_type _card;

	public:

		card_location ( stack_location const & stack , card_reference_type const & card );

		stack_location const & stack () const;
		card_reference_type const & card () const;
};

}

#endif

