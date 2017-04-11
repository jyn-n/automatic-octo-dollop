
#include "player_location.hpp"

namespace game {

player_location::player_location ( value_type && value )
: enum_class_type ( std::move ( value ) )
{
	construct ( *this );
}

player_location::~player_location ()
{
	destruct ( *this );
}

bool operator< ( player_location const & lhs , player_location const & rhs )
{
	return std::less < player_location::enum_class_type > () ( lhs , rhs );
}

player_location const player_location::deck ( "deck" );
player_location const player_location::hand ( "hand" );
player_location const player_location::discard ( "discard" );
player_location const player_location::reveal ( "reveal" );
player_location const player_location::play ( "play" );

}

