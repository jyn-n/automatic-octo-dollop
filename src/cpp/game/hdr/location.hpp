
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "common/enum_class.hpp"
#include "core_types.hpp"

namespace game {

class location : public common::enum_class < core_types::key_type , location >
{
	public:

		location ( value_type && value_type );
		virtual ~location ();

		static location const player;
};

bool operator< ( location const & lhs , location const & rhs );

}

#endif

