
namespace common {

template < typename T , typename B >
enum_class<T,B>::enum_class ( value_type && value , base_type const & b )
: _value ( std::move ( value ) )
, _this ( b )
{
	_instances.insert(_this);
}

template < typename T , typename B >
enum_class<T,B>::~enum_class ()
{
	_instances.erase(_this);
}

template < typename T , typename B >
enum_class<T,B>::operator value_type const & () const
{
	return _value;
}

template < typename T , typename B >
auto enum_class<T,B>::begin () -> const_iterator
{
	return _instances.cbegin();
}

template < typename T , typename B >
auto enum_class<T,B>::end () -> const_iterator
{
	return _instances.cend();
}

template < typename T , typename B >
bool operator< ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs )
{
	return std::less < typename enum_class<T,B>::value_type > () ( lhs , rhs );
}

}

