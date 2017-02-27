
#ifndef CARDWORLD_HPP
#define CARDWORLD_HPP

#include "cardstack.hpp"

class cardworld {

	public:

		using this_type = cardworld;
		using cardstack_type = cardstack;
		using key_type = cardstack::key_type;

		using card_type = cardstacL_type::value_type;

		class stack_location;
		class card_location;

	private:

		using container_type = std::map < key_type , this_type >;

		cardstack_type _stack;
		container_type _children;

	public:

		cardworld () = default;

		cardstack_type & cardstack ();
		cardstack_type const & cardstack ();

		cardstack_type & operator[] ( stack_location const & location );
		cardstack_type const & at ( stack_location const & location ) const;

		card_type & operator[] ( card_location const & location );
		card_type const & at ( card_location const & location ) const;

};

#endif

