
namespace common {

template < typename T , typename B >
typename enum_class<T,B>::container_type enum_class<T,B>::_instances;

template < typename T , typename B >
enum_class<T,B>::enum_class ( value_type && value )
: _value ( std::move ( value ) )
{
}

template < typename T , typename B >
enum_class<T,B>::~enum_class ()
{
}
/*
template < typename T , typename B >
enum_class<T,B>::operator value_type () const
{
	return _value;
}
*/
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
void enum_class<T,B>::construct ( base_type const & value )
{
	_instances.insert ( value );
}

template < typename T , typename B >
void enum_class<T,B>::destruct ( base_type const & value )
{
	_instances.erase ( value );
}

template < typename T , typename B >
bool operator< ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs )
{
	return std::less < typename enum_class<T,B>::value_type > () ( lhs , rhs );
}

}

