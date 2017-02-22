
#ifndef CARDSTACK_HPP
#define CARDSTACK_HPP

#include <string>
#include <map>
#include <vector>

#include "game_object"

class cardstack {

	public:

		using this_type = cardstack;

		using key_type = std::string;
		using value_type = game_object;

	private:

		using container_type = std::map < key_type , value_type >;
		using order_container_type = std::vector < key_type >;

		container_type _cards;
		order_container_type _order;

	public:

		using size_type = container_type::size_type;
		using order_type = order_container_type::size_type;

	public:

		size_type size () const;

		value_type & operator[] ( key_type const & key );
		value_type const & operator[] ( key_type const & key ) const;

		value_type & operator[] ( order_type const & position );
		value_type const & operator[] ( order_type const & position ) const;

		key_type insert ( value_type && value );
		value_type erase ( key_type const & key );
		value_type erase ( order_type const & position );

		template < typename Rng >
		this_type & shuffle ( Rng & rng );
};

#include "cardstack.inl"

#endif

