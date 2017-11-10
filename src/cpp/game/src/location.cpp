
#include "location.hpp"

namespace game {

location::location ( value_type && value )
: enum_class_type ( std::move ( value ) , *this )
{
}

location::~location ()
{
}

template<>
typename location::enum_class_type::container_type location::enum_class_type::_instances {};

location const location::player ( "player" );

}

