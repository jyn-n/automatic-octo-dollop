
#ifndef PLAYER_LOCATION
#define PLAYER_LOCATION

#include "common/enum_class.hpp"
#include "core_types.hpp"

namespace game {

class player_location : public common::enum_class < core_types::key_type , player_location >
{
	public:

		player_location ( value_type && value_type );
		virtual ~player_location ();

		static player_location const deck;
		static player_location const hand;
		static player_location const discard;
		static player_location const reveal;
		static player_location const play;
};

bool operator< ( player_location const & lhs , player_location const & rhs );

}

#endif

