
template < typename Begin , typename End = Begin >
inline
iterator_range<Begin,End>::iterator_range ( begin_type const & begin , end_type const & end )
: _begin ( begin )
, _end ( end )
{
}

template < typename Begin , typename End = Begin >
inline
auto iterator_range<Begin,End>::begin () const -> begin_type 
{
	return begin;
}

template < typename Begin , typename End = Begin >
inline
auto iterator_range<Begin,End>::end () const -> end_type 
{
	return end;
}

template < typename Begin , typename End = Begin >
inline
iterator_range < Begin , End > make_range<Begin,End> ( Begin begin , End end )
{
	return iterator_range < Begin , End > ( begin , end );
}

