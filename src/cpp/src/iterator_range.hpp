
#ifndef ITERATOR_RANGE_HPP
#define ITERATOR_RANGE_HPP

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

		begin_type begin () const;
		end_type end () const;
};

template < typename Begin , typename End = Begin >
iterator_range < Begin , End > make_range ( Begin begin , End end );

#include "iterator_range.inl"

#endif

