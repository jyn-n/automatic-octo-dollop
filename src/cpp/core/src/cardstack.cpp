
#include "cardstack.hpp"

namespace core {

auto cardstack::size () const -> size_type 
{
	return _cards.size();
}

auto cardstack::begin () -> iterator 
{
	return iterator ( *this , _order.begin() );
}

auto cardstack::end () -> iterator 
{
	return iterator ( *this , _order.end() );
}

auto cardstack::begin () const -> const_iterator 
{
	return cbegin();
}

auto cardstack::end () const -> const_iterator 
{
	return cend();
}

auto cardstack::cbegin () const -> const_iterator 
{
	return const_iterator ( *this , _order.begin() );
}

auto cardstack::cend () const -> const_iterator 
{
	return const_iterator ( *this , _order.cend() );
}

auto cardstack::operator[] ( key_type const & key ) -> value_type & 
{
	return _cards.at ( key );
}

auto cardstack::operator[] ( key_type const & key ) const -> value_type const & 
{
	return _cards.at ( key );
}

auto cardstack::operator[] ( order_type const & position ) -> value_type & 
{
	return (*this) [ _order [ position ] ];
}

auto cardstack::operator[] ( order_type const & position ) const -> value_type const & 
{
	return (*this) [ _order [ position ] ];
}

auto cardstack::insert ( value_type && value ) -> key_type 
{
	auto key = std::to_string ( value.id() );
	_cards.insert ( std::make_pair ( key , std::move ( value ) ) );
	_order.push_back ( key );
	return key;
}

#include <algorithm>

auto cardstack::erase ( key_type const & key ) -> value_type 
{
	_order.erase ( std::remove ( _order.begin() , _order.end() , key ) , _order.end() );

	auto result = std::move ( _cards.at ( key ) );
	_cards.erase ( key );
	return result;
}

auto cardstack::erase ( order_type const & position ) -> value_type 
{
	auto key = _order [ position ];
	return erase ( key );
}

}

