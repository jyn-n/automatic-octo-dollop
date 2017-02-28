
#include "cardworld_stack_location.hpp"


cardworld::stack_location::stack_location ( container_type const & items )
: _items ( items )
{
}

cardworld::stack_location::stack_location ( container_type && items )
: _items ( std::move ( items ) )
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

