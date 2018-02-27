
namespace common {

template < typename T , typename B >
inline
enum_class<T,B>::enum_class ( value_type && value , base_type const & b )
: _value ( std::move ( value ) )
, _this ( b )
{
	_instances.insert(_this);
}

template < typename T , typename B >
inline
enum_class<T,B>::~enum_class ()
{
	_instances.erase(_this);
}

template < typename T , typename B >
inline
enum_class<T,B>::operator value_type const & () const
{
	return _value;
}

template < typename T , typename B >
inline
auto enum_class<T,B>::begin () -> const_iterator
{
	return _instances.cbegin();
}

template < typename T , typename B >
inline
auto enum_class<T,B>::end () -> const_iterator
{
	return _instances.cend();
}

template < typename T , typename B >
inline
bool operator< ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs )
{
	return std::less < typename enum_class<T,B>::value_type > () ( lhs , rhs );
}

template < typename T , typename B >
inline
bool operator== ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs )
{
	return (!(lhs < rhs)) && (!(rhs < lhs));
}

template <typename T>
inline
bool operator== (std::reference_wrapper<T> const & lhs , std::reference_wrapper<T> const & rhs)
{
	return lhs.get() == rhs.get();
}

template < typename T , typename B >
inline
bool operator== ( enum_class<T,B> const & lhs , B const & rhs )
{
	return lhs.get() == rhs;
}

template < typename T , typename B >
inline
bool operator== ( B const & lhs , enum_class<T,B> const & rhs )
{
	return rhs == lhs;
}

template < typename T , typename B >
inline
bool operator== ( std::reference_wrapper<B const> const & lhs , T const & rhs )
{
	return static_cast<T> (lhs.get()) == rhs;
}

template < typename T , typename B >
inline
bool operator== ( enum_class<T,B> const & lhs , B const & rhs );

template < typename T , typename B >
inline
bool operator== ( B const & rhs , enum_class<T,B> const & lhs );

template < typename T , typename B >
inline
auto enum_class<T,B>::id ( base_type const & b ) -> size_type 
{
	return std::distance ( _instances.begin() , std::find ( _instances.begin() , _instances.end() , std::reference_wrapper<base_type const> (b) ) );
}

template < typename T , typename B >
inline
auto enum_class<T,B>::from_id ( size_type const & i ) -> base_type const &
{
	return *std::next( _instances.begin() , i );
}

template < typename T , typename B >
inline
auto enum_class<T,B>::from_value ( value_type const & value ) -> base_type const & 
{
	//TODO throw
	//TODO
	//return std::find ( _instances.begin() , _instances.end() , value );
}


}

