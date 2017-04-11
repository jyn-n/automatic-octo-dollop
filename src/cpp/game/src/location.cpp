
#include "location.hpp"

namespace game {

location::location ( value_type && value )
: enum_class_type ( std::move ( value ) )
{
	construct ( *this );
}

location::~location ()
{
	destruct ( *this );
}

bool operator< ( location const & lhs , location const & rhs )
{
	return std::less < location::enum_class_type > () ( lhs , rhs );
}

location location::player ( "player" );

}

