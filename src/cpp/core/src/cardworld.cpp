
#include "cardworld.hpp"

#include "cardworld_stack_location.hpp"
#include "cardworld_card_location.hpp"

namespace core {

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

auto cardworld::operator[] ( card_location const & location ) -> card_type & 
{
	return (*this) [ location.stack() ] [ location.card() ];
}

auto cardworld::at ( card_location const & location ) const -> card_type const & 
{
	return at ( location.stack() ) [ location.card() ];
}

auto cardworld::insert ( stack_location const & destination , game_object && card ) -> card_location 
{
	return card_location ( destination , (*this) [ destination ].insert ( std::move (card) ) );
}

auto cardworld::erase ( card_location const & location ) -> game_object 
{
	return (*this) [ location.stack() ].erase ( location.card() );
}

auto cardworld::erase ( stack_location const & location , order_type const & position ) -> game_object 
{
	return (*this) [ location ].erase ( position );
}

auto cardworld::move ( card_location const & origin , stack_location const & destination ) -> card_location 
{
	return insert ( destination , erase ( origin ) );
}

auto cardworld::move ( stack_location const & origin , order_type const & position , stack_location const & destination ) -> card_location 
{
	return insert ( destination , erase ( origin , position ) );
}

}

