
#ifndef CARDSTACK_HPP
#define CARDSTACK_HPP

#include <string>
#include <map>
#include <vector>

#include "game_object.hpp"

namespace core {

class cardstack {

	public:

		using this_type = cardstack;

		using key_type = std::string;
		using value_type = game_object;

	private:

		using container_type = std::map < key_type , value_type >;
		using order_container_type = std::vector < key_type >;

		template < typename Base , typename Value >
		class basic_iterator;

		container_type _cards;
		order_container_type _order;

	public:

		using size_type = container_type::size_type;
		using order_type = order_container_type::size_type;

		using iterator = basic_iterator < this_type , value_type >;
		using const_iterator = basic_iterator < this_type const , value_type const >;

	public:

		cardstack() = default;

		size_type size () const;

		iterator begin ();
		iterator end ();
		const_iterator begin () const;
		const_iterator end () const;
		const_iterator cbegin () const;
		const_iterator cend () const;

		value_type & operator[] ( key_type const & key );
		value_type const & operator[] ( key_type const & key ) const;

		value_type & operator[] ( order_type const & position );
		value_type const & operator[] ( order_type const & position ) const;

		key_type insert ( value_type && value );
		value_type erase ( key_type const & key );
		value_type erase ( order_type const & position );

		template < typename Rng >
		this_type & shuffle ( Rng && rng );
};

}

#include "cardstack_basic_iterator.hpp"

#include "cardstack.inl"


#endif

