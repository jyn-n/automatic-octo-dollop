
#include "player_location.hpp"

namespace game {

player_location::player_location ( value_type && value )
: enum_class_type ( std::move ( value ) , *this )
{
}

player_location::~player_location ()
{
}

template<>
typename player_location::enum_class_type::container_type player_location::enum_class_type::_instances {};

player_location const player_location::deck ( "deck" );
player_location const player_location::hand ( "hand" );
player_location const player_location::discard ( "discard" );
player_location const player_location::reveal ( "reveal" );
player_location const player_location::play ( "play" );

}

