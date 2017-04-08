
#include "game_object.hpp"

namespace core {

game_object::id_factory_type game_object::_id_factory {};

game_object::game_object ( object_base_type const & base )
: _base ( base )
, _id ( _id_factory() )
, _valid ( true )
{
}

game_object::~game_object ()
{
	if ( ! _valid ) return;
	_id_factory.free ( id() );
}

game_object::game_object ( this_type && rhs )
: _base ( rhs._base )
, _id ( rhs._id )
, _valid ( rhs._valid )
{
	rhs._valid = false;
}

/*
auto game_object::operator== ( this_type const & rhs ) const -> bool 
{
	return id() == rhs.id();
}
*/
auto game_object::at ( key_type const & key ) const -> value_type const & 
{
	if ( ! _attributes.count ( key ) ) return _base.at ( key );
	return _attributes.at ( key );
}

auto game_object::operator[] ( key_type const & key ) -> value_type & 
{
	if ( _attributes.count ( key ) ) return _attributes.at ( key );

	if ( _base.count ( key ) )
		_attributes [ key ] = _base.at ( key );

	return _attributes [ key ];
}

auto game_object::id () const -> id_type const & 
{
	return _id;
}

}

