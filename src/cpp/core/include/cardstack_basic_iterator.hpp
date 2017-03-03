
#ifndef CARDSTACK_BASIC_ITERATOR_HPP
#define CARDSTACK_BASIC_ITERATOR_HPP

#include "cardstack.hpp"

template < typename Base , typename Value >
class cardstack::basic_iterator {

	private:

		using this_type = basic_iterator<Base,Value>;

	public:

		using base_type = Base;
		using value_type = Value;
		using iterator_type = order_container_type::const_iterator;

	private:

		base_type & _base;
		iterator_type _iterator;

	public:

		basic_iterator ( base_type & base , iterator_type const & iterator );

		//TODO implement all the other bullshit

		value_type & operator* () const;

		this_type & operator++ ();

		bool operator== ( this_type const & rhs ) const;
		bool operator!= ( this_type const & rhs ) const;
};

#include "cardstack_basic_iterator.inl"

#endif

