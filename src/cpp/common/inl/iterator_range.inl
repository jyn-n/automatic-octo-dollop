
namespace common {

template < typename Begin , typename End >
inline
iterator_range<Begin,End>::iterator_range ( begin_type const & begin , end_type const & end )
: _begin ( begin )
, _end ( end )
{
}

template < typename Begin , typename End >
template < typename T >
inline
iterator_range<Begin,End>::iterator_range ( T const & t )
: _begin ( std::begin (t) )
, _end ( std::end (t) )
{
}

template < typename Begin , typename End >
inline
auto iterator_range<Begin,End>::begin () const -> begin_type 
{
	return _begin;
}

template < typename Begin , typename End >
inline
auto iterator_range<Begin,End>::begin () -> begin_type & 
{
	return _begin;
}

template < typename Begin , typename End >
inline
auto iterator_range<Begin,End>::end () const -> end_type 
{
	return _end;
}

template < typename Begin , typename End >
inline
auto iterator_range<Begin,End>::empty () const -> bool 
{
	return _begin == _end;
}

template < typename Begin , typename End >
inline
iterator_range<Begin,End> make_range ( Begin begin , End end )
{
	return iterator_range < Begin , End > ( begin , end );
}

template < typename T >
auto make_range ( T const & t ) -> iterator_range < decltype (std::begin(t)) , decltype (std::end(t)) >
{
	return iterator_range <decltype(std::begin(t)),decltype(std::end(t))> (t);
}

}

