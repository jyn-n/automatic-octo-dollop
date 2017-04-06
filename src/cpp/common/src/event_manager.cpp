
#include "event_manager.hpp"

event_manager::event_manager ()
: _events()
{
}

auto event_manager::register_event ( key_type const & key , event_type && value) -> this_type &
{
	_events [ key ].push_back ( std::move (value) );
	return *this;
}

auto event_manager::operator() ( key_type const & key , event_context_type & context ) -> this_type &
{
	for ( auto & f : _events [ key ] )
		f ( context );

	return *this;
}

