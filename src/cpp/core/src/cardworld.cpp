
#include "cardworld.hpp"

#include "cardworld_stack_location.hpp"
#include "cardworld_card_location.hpp"

namespace core {

template < typename T >
auto cardworld::make_card_location ( stack_location const & stack , T const & t ) -> card_location<T> 
{
	return card_location<T> ( stack , t );
}

template auto cardworld::make_card_location<cardworld::key_type> ( stack_location const & stack , key_type const & t ) -> card_location<key_type>;
template auto cardworld::make_card_location<cardworld::order_type> ( stack_location const & stack , order_type const & t ) -> card_location<order_type>;

auto cardworld::stack () -> cardstack_type & 
{
	return _stack;
}

auto cardworld::stack () const -> cardstack_type const & 
{
	return _stack;
}

auto cardworld::operator[] ( stack_location const & location ) -> cardstack_type & 
{
	auto range = common::make_range ( location );
	return (*this) [ range ];
}

auto cardworld::at ( stack_location const & location ) const -> cardstack_type const & 
{
	auto range = common::make_range ( location );
	return at ( range );
}

template < typename T >
auto cardworld::operator[] ( card_location<T> const & location ) -> card_type & 
{
	return (*this) [ location.stack() ] [ location.card() ];
}

template auto cardworld::operator[]<cardworld::key_type> ( card_location <key_type> const & ) -> card_type &;
template auto cardworld::operator[]<cardworld::order_type> ( card_location <order_type> const & ) -> card_type &;

template < typename T >
auto cardworld::at ( card_location<T> const & location ) const -> card_type const & 
{
	return at ( location.stack() ) [ location.card() ];
}

template auto cardworld::at<cardworld::key_type> ( card_location <key_type> const & ) const -> card_type const &;
template auto cardworld::at<cardworld::order_type> ( card_location <order_type> const & ) const -> card_type const &;

auto cardworld::insert ( stack_location const & destination , game_object && card ) -> key_card_location
{
	return card_location < key_type > ( destination , (*this) [ destination ].insert ( std::move (card) ) );
}

template < typename T >
auto cardworld::erase ( card_location<T> const & location ) -> game_object 
{
	return (*this) [ location.stack() ].erase ( location.card() );
}

template auto cardworld::erase<cardworld::key_type> ( card_location<key_type> const & location ) -> game_object;
template auto cardworld::erase<cardworld::order_type> ( card_location<order_type> const & location ) -> game_object;

template < typename T >
auto cardworld::move ( card_location<T> const & origin , stack_location const & destination ) -> key_card_location
{
	return insert ( destination , erase ( origin ) );
}

template auto cardworld::move<cardworld::key_type> ( card_location<key_type> const & origin , stack_location const & destination ) -> card_location < key_type >;
template auto cardworld::move<cardworld::order_type> ( card_location<order_type> const & origin , stack_location const & destination ) -> card_location < key_type >;

}

