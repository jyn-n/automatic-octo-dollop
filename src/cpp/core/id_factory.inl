

template < typename T >
inline
id_factory<T>::id_factory ()
: _current (0)
, _free_ids ()
{
}

template < typename T >
inline
auto id_factory<T>::operator() () -> id_type 
{
	if (_free_ids.empty()) return _current++;

	auto result = *_free_ids.begin();
	_free_ids.erase(_free_ids.begin());
	return result;
}

template < typename T >
inline
auto id_factory<T>::free ( id_type id ) -> this_type &
{
	_free_ids.insert ( id );
	while ( ! _free_ids.empty() ) {
		auto position = _free_ids.end();
		--position;
		if ( *position != _current ) break;
		_free_ids.erase ( position );
		--_current;
	}
	return *this;
}

