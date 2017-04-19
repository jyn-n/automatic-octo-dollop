
namespace common {

template < typename Key , template < Key key > typename Parameters >
template < Key key , typename ... Args >
inline
auto event_manager<Key,Parameters>::_container () -> std::enable_if_t < std::is_same < typelist < Args ... > , parameters_t < key > >::value , container_type < Args ... > & >
{
	static container_type < Args ... > container;
	return container;
}

template < typename Key , template < Key key > typename Parameters >
template < Key key , typename ... Args >
inline
auto event_manager<Key,Parameters>::register_event ( event_type<Args...> && event ) -> this_type & 
{
	_container < key , Args ... > () .push_back ( std::move ( event ) );

	return *this;
}

template < typename Key , template < Key key > typename Parameters >
template < Key key , typename ... Args >
inline
auto event_manager<Key,Parameters>::operator() ( Args ... args ) -> this_type & 
{
	for ( auto & f : _container < key , Args ... > () ) {
		f ( args ... );
	}

	return *this;
}

}

