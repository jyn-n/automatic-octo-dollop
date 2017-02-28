
#include "cardworld_card_location.hpp"


cardworld::card_location::card_location ( stack_location const & stack , key_type const & card )
: _stack ( stack )
, _card ( card )
{
}

auto cardworld::card_location::stack () const -> stack_location const & 
{
	return _stack;
}

auto cardworld::card_location::card () const -> key_type const & 
{
	return _card;
}

