
#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <vector>

namespace common {

template < typename ... Args >
class typelist {

	public:

		typelist() = delete;
};

template < typename Key , template < Key key > typename Parameters >
class event_manager {

	public:

		using this_type = event_manager<Key , Parameters>;

		template < typename ... Args >
		using event_type = std::function < void (Args ... args) >;

		using key_type = Key;

	private:

		template < key_type key >
		using parameters_t  = typename Parameters < key >::type;

		template < typename ... Args >
		using container_type = std::vector < event_type < Args ... > >;

		template < key_type key , typename ... Args >
		std::enable_if_t < std::is_same < typelist < Args ... > , parameters_t < key > >::value , container_type < Args ... > & > _container ();

	public:

		template < key_type key , typename ... Args >
		this_type & register_event ( event_type<Args...> && event );

		template < key_type key , typename ... Args >
		this_type & operator() ( Args ... args );
};

}

#include "event_manager.inl"

#endif

