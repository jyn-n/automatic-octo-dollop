
auto cardstack::size () const -> size_type 
{
	return _cards.size();
}

auto cardstack::operator[] ( key_type const & key ) -> value_type & 
{
	return _cards.at ( key );
}

auto cardstack::operator[] ( key_type const & key ) const -> value_type const & 
{
	return _cards.at ( key );
}

auto cardstack::operator[] ( order_type const & position ) -> value_type & 
{
	return (*this) [ _order [ position ] ]
}

auto cardstack::operator[] ( order_type const & position ) const -> value_type const & 
{
	return (*this) [ _order [ position ] ]
}

auto cardstack::insert ( value_type && value ) -> key_type 
{
	auto key = _cards [ value.id() ] = std::move ( value );
	_order.push_back ( key );
	return key;
}

auto cardstack::erase ( key_type const & key ) -> value_type 
{
	for ( auto it = _order.begin(); it != _order.end(); ++it ) if ( *it == key ) _order.erase ( it );

	auto result = std::move ( _cards.at ( key ) );
	_cards.erase ( key );
	return result;
}

auto cardstack::erase ( order_type const & position ) -> value_type 
{
	return erase ( _order [ position ] );
}

