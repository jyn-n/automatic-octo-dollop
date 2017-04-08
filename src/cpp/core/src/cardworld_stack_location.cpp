
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

}

