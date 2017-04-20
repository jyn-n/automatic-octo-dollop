
namespace common {

template < typename Key , template < Key key > typename Events >
template < Key key >
inline
auto event_manager<Key,Events>::_container () -> container_type < event_type < key > > &
{
	static container_type < event_type < key > > container;
	return container;
}

template < typename Key , template < Key key > typename Events >
template < Key key >
inline
auto event_manager<Key,Events>::register_event ( event_type<key> && event ) -> this_type & 
{
	_container < key > () .push_back ( std::move ( event ) );

	return *this;
}

template < typename Key , template < Key key > typename Events >
template < Key key , typename ... Args >
inline
auto event_manager<Key,Events>::operator() ( Args ... args ) -> this_type & 
{
	for ( auto & f : _container < key > () ) {
		f ( args ... );
	}

	return *this;
}

}

