
#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <vector>

namespace common {

template < typename ... Args >
using event_type = std::function < void (Args...) >;

template < typename Key , template < Key key > typename Events >
class event_manager {

	public:

		using this_type = event_manager<Key , Events>;
		using key_type = Key;

	private:

		template < key_type key >
		using event_type = typename Events < key >::type;

		template < typename T >
		using container_type = std::vector < T >;

		template < key_type key >
		container_type < event_type < key > > & _container ();

	public:

		template < key_type key >
		this_type & register_event ( event_type<key> && event );

		template < key_type key , typename ... Args >
		this_type & operator() ( Args ... args );
};

}

#include "event_manager.inl"

#endif

