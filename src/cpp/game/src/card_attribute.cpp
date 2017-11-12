
#include "card_attribute.hpp"

namespace game {

card_attribute::card_attribute ( value_type && value )
: enum_class_type ( std::move ( value ) , *this )
{
}

card_attribute::~card_attribute ()
{
}

template<>
typename card_attribute::enum_class_type::container_type card_attribute::enum_class_type::_instances {};

card_attribute const card_attribute::title ( "title" );
card_attribute const card_attribute::effect ( "effect" );
card_attribute const card_attribute::time ( "time" );
card_attribute const card_attribute::check_size ( "check_size" );
card_attribute const card_attribute::successes ( "successes" );

}

