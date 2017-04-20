
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

		template
		< typename T
		, typename = typename std::enable_if_t
			<  std::is_same < T , cardworld::key_type >::value
			|| std::is_same < T , cardworld::order_type >::value
			>
		>
		class card_location;

		using key_card_location = card_location < key_type >;
		using order_card_location = card_location < order_type >;

		class any_card_location;

		template < typename T >
		static
		card_location<T> make_card_location ( stack_location const & stack , T const & t );

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

		template < typename T >
		card_type & operator[] ( card_location<T> const & location );
		template < typename T >
		card_type const & at ( card_location<T> const & location ) const;

		card_type & operator[] ( any_card_location const & location );
		card_type const & at ( any_card_location const & location ) const;

		key_card_location insert ( stack_location const & destination , game_object && card );

		template < typename T >
		game_object erase ( card_location<T> const & location );

		template < typename T >
		key_card_location move ( card_location<T> const & origin , stack_location const & destination );

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

