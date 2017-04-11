
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include "common/enum_class.hpp"

namespace game {

class location : public common::enum_class < std::string , location >
{
	public:

		location ( value_type && value_type );
		virtual ~location ();

		static location player;
};

bool operator< ( location const & lhs , location const & rhs );

}

#endif

