
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

}

