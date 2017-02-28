
#include "cardworld.hpp"

#include "cardworld_stack_location.hpp"
#include "cardworld_card_location.hpp"

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
	auto range = make_range ( location );
	return (*this) [ range ];
}

auto cardworld::at ( stack_location const & location ) const -> cardstack_type const & 
{
	auto range = make_range ( location );
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

