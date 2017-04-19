
#ifndef CARDWORLD_CARD_LOCATION_HPP
#define CARDWORLD_CARD_LOCATION_HPP

#include "cardworld_stack_location.hpp"
#include "cardworld.hpp"

#include <experimental/optional>

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

namespace stde = std::experimental;

class cardworld::any_card_location {

	public:

		using optional_key = stde::optional < key_card_location >;
		using optional_order = stde::optional < order_card_location >;

	private:

		optional_key _key;
		optional_order _order;

	public:

		any_card_location ( key_card_location && key );
		any_card_location ( order_card_location && order );

		bool valid_key () const;
		bool valid_order () const;

		key_card_location const & key () const;
		order_card_location const & order () const;
};

}

#endif

