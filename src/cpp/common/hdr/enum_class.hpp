
#ifndef ENUM_CLASS_HPP
#define ENUM_CLASS_HPP

#include <set>
#include <functional>
#include <vector>

namespace common {

template < typename T , typename Base >
class enum_class {

	public:

		using value_type = T;
		using this_type = enum_class < T , Base >;
		using enum_class_type = this_type;

	private:

		value_type _value;

	protected:

		using base_type = Base;
		using container_type = std::set < std::reference_wrapper< base_type const > , std::less < this_type > >;

	private:

		base_type const & _this;

	public:

		using const_iterator = typename container_type::const_iterator;
		using size_type = typename container_type::size_type;

		static container_type _instances;

	protected:

		enum_class ( value_type && value , base_type const & b );

	public:

		virtual ~enum_class ();

		operator value_type const & () const;

		static const_iterator begin ();
		static const_iterator end ();

		static size_type id ( base_type const & b );
		static base_type const & from_id ( size_type const & i );

		static base_type const & from_value ( value_type const & value );
};

template < typename T , typename B >
bool operator< ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs );

template < typename T , typename B >
bool operator== ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs );

}

#include "enum_class.inl"

#endif

