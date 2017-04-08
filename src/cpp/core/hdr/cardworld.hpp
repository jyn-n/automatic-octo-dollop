
#ifndef CARDWORLD_HPP
#define CARDWORLD_HPP

#include "cardstack.hpp"

namespace common {

template < typename Begin , typename End >
class iterator_range;

}

namespace core {

class cardworld {

	public:

		using this_type = cardworld;
		using cardstack_type = cardstack;
		using key_type = cardstack::key_type;

		using card_type = cardstack_type::value_type;
		using order_type = cardstack_type::order_type;

		template < typename Begin , typename End >
		using iterator_range = common::iterator_range<Begin,End>;

		class stack_location;
		class card_location;

	private:

		using container_type = std::map < key_type , this_type >;

		cardstack_type _stack;
		container_type _children;

	public:

		cardworld () = default;

		cardstack_type & stack ();
		cardstack_type const & stack () const;

		cardstack_type & operator[] ( stack_location const & location );
		cardstack_type const & at ( stack_location const & location ) const;

		card_type & operator[] ( card_location const & location );
		card_type const & at ( card_location const & location ) const;

		card_location insert ( stack_location const & destination , game_object && card );
		game_object erase ( card_location const & location );
		game_object erase ( stack_location const & location , order_type const & position );
		card_location move ( card_location const & origin , stack_location const & destination );
		card_location move ( stack_location const & origin , order_type const & position , stack_location const & destination );

	private:

		template < typename Begin , typename End = Begin >
		cardstack_type & operator[] ( iterator_range<Begin,End> & range );

		template < typename Begin , typename End = Begin >
		cardstack_type const & at ( iterator_range<Begin,End> & range ) const;
};

}

#include "cardworld.inl"

#include "cardworld_stack_location.hpp"

#ifndef CARDWORLD_STACK_LOCATION_CPP
	#include "cardworld_card_location.hpp"
#endif

#endif

