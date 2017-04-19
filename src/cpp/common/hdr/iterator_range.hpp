
#ifndef ITERATOR_RANGE_HPP
#define ITERATOR_RANGE_HPP

#include <type_traits>

namespace common {

template < typename Begin , typename End = Begin >
class iterator_range {

	public:

		using this_type = iterator_range < Begin , End >;

	private:

		using begin_type = Begin;
		using end_type = End;

		begin_type _begin;
		end_type _end;

	public:

		iterator_range ( begin_type const & begin , end_type const & end );
		template < typename T >
		iterator_range ( T const & t );

		begin_type begin () const;
		begin_type & begin ();
		end_type end () const;
		bool empty () const;
};

template < typename Begin , typename End = Begin >
iterator_range < std::decay_t<Begin> , std::decay_t<End> > make_range ( Begin begin , End end );

template < typename T >
auto make_range ( T const & t ) -> iterator_range < decltype (std::begin(t)) , decltype (std::end(t)) >;

}

#include "iterator_range.inl"

#endif

