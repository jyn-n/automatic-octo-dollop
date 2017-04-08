
namespace core {

template < typename Base , typename Value >
cardstack::basic_iterator<Base,Value>::basic_iterator ( base_type & base , iterator_type const & iterator )
: _base ( base )
, _iterator ( iterator )
{
}

template < typename Base , typename Value >
inline
auto cardstack::basic_iterator<Base,Value>::operator* () const -> value_type & 
{
	return _base [*_iterator];
}

template < typename Base , typename Value >
inline
auto cardstack::basic_iterator<Base,Value>::operator++ () -> this_type &
{
	++_iterator;
	return *this;
}

template < typename Base , typename Value >
inline
auto cardstack::basic_iterator<Base,Value>::operator== ( this_type const & rhs ) const -> bool 
{
	return _iterator == rhs._iterator;
}

template < typename Base , typename Value >
inline
auto cardstack::basic_iterator<Base,Value>::operator!= ( this_type const & rhs ) const -> bool 
{
	return _iterator != rhs._iterator;
}

}

