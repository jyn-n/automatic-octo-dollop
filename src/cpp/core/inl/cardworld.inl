
#include "iterator_range.hpp"

template < typename Begin , typename End = Begin >
inline
auto cardworld::operator[] ( iterator_range<Begin,End> & range ) -> cardstack_type & 
{
	if ( range.empty() ) return stack();
	auto & child = _children [ *range.begin() ];
	++range.begin();
	return child [ range ];
}

template < typename Begin , typename End = Begin >
inline
auto cardworld::at ( iterator_range<Begin,End> & range ) const -> cardstack_type const &
{
	if ( range.empty() ) return stack();
	auto & child = _children.at ( *range.begin() );
	++range.begin();
	return child.at ( range );
}

