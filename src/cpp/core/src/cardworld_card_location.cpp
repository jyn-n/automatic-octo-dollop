
#include "cardworld_card_location.hpp"

namespace core {

template < typename T , typename E >
cardworld::card_location<T,E>::card_location ( stack_location const & stack , card_reference_type const & card )
: _stack ( stack )
, _card ( card )
{
}

template < typename T , typename E >
auto cardworld::card_location<T,E>::stack () const -> stack_location const & 
{
	return _stack;
}

template < typename T , typename E >
auto cardworld::card_location<T,E>::card () const -> card_reference_type const & 
{
	return _card;
}

template class cardworld::card_location < cardworld::key_type >;
template class cardworld::card_location < cardworld::order_type >;

cardworld::any_card_location::any_card_location ( key_card_location && key )
: _key ( std::move(key) )
, _order ()
{
}

cardworld::any_card_location::any_card_location ( order_card_location && order )
: _key ()
, _order ( std::move(order) )
{
}

bool cardworld::any_card_location::any_card_location::valid_key () const
{
	return static_cast<bool> (_key);
}

bool cardworld::any_card_location::any_card_location::valid_order () const
{
	return static_cast<bool> (_order);
}

auto cardworld::any_card_location::key () const -> key_card_location const &
{
	return *_key;
}

auto cardworld::any_card_location::order () const -> order_card_location const &
{
	return *_order;
}

}

