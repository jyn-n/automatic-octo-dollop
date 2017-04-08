
#include "event_manager.hpp"

namespace common {

template < typename Event_Context >
event_manager<Event_Context>::event_manager ()
: _events()
{
}

template < typename Event_Context >
auto event_manager<Event_Context>::register_event ( key_type const & key , event_type && value) -> this_type &
{
	_events [ key ].push_back ( std::move (value) );
	return *this;
}

template < typename Event_Context >
auto event_manager<Event_Context>::operator() ( key_type const & key , event_context_type & context ) -> this_type &
{
	for ( auto & f : _events [ key ] )
		f ( context );

	return *this;
}

}

