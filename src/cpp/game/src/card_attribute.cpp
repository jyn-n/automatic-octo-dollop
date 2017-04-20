
#include "card_attribute.hpp"

namespace game {

card_attribute::card_attribute ( value_type && value )
: enum_class_type ( std::move ( value ) )
{
	construct ( *this );
}

card_attribute::~card_attribute ()
{
	destruct ( *this );
}

bool operator< ( card_attribute const & lhs , card_attribute const & rhs )
{
	return std::less < card_attribute::enum_class_type > () ( lhs , rhs );
}

card_attribute const card_attribute::title ( "title" );
card_attribute const card_attribute::effect ( "effect" );
card_attribute const card_attribute::time ( "time" );
card_attribute const card_attribute::check_size ( "check_size" );
card_attribute const card_attribute::successes ( "successes" );

}

