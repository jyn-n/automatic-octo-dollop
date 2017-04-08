
#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <map>
#include <vector>

namespace common {

template < typename Event_Context >
class event_manager {

	public:

		using event_context_type = Event_Context;
		using event_type = std::function < void (event_context_type &) >;
		using this_type = event_manager<Event_Context>;
		using key_type = std::string;

	private:

		using event_container_type = std::vector < event_type >;
		using container_type = std::map < key_type , event_container_type >;

		container_type _events;

	public:

		event_manager ();

		this_type & register_event ( key_type const & key , event_type && value);

		this_type & operator() ( key_type const & key , event_context_type & context );

};

}

#include "event_manager.inl"

#endif

