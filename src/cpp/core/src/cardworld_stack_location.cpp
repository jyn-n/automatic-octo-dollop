
#define CARDWORLD_STACK_LOCATION_CPP

#include "cardworld_stack_location.hpp"

namespace core {

cardworld::stack_location::stack_location ( container_type const & items )
: _items ( items )
{
}

cardworld::stack_location::stack_location ( container_type && items )
: _items ( std::move ( items ) )
{
}

cardworld::stack_location::stack_location ( std::initializer_list < key_type > keys )
: _items ( keys )
{
}

auto cardworld::stack_location::begin () const -> const_iterator 
{
	return _items.begin ();
}

auto cardworld::stack_location::end () const -> const_iterator 
{
	return _items.end ();
}

auto cardworld::stack_location::operator== ( stack_location const & rhs ) const -> bool
{
	auto l = begin();
	auto r = rhs.begin();

	while ( l != end() && r != rhs.end() )
	{
		if ( *l != *r ) return false;
		++l; ++r;
	}

	return l == end() && r == rhs.end();
}

auto cardworld::stack_location::operator!= ( stack_location const & rhs ) const -> bool
{
	return !((*this) == rhs);
}

}

