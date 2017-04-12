
#ifndef ENUM_CLASS_HPP
#define ENUM_CLASS_HPP

#include <set>
#include <functional>

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
		using container_type = std::set < std::reference_wrapper < base_type const > >;

	public:

		using const_iterator = typename container_type::const_iterator;

		static container_type _instances;

		static void construct ( base_type const & value );
		static void destruct ( base_type const & value );

	protected:

		enum_class ( value_type && value );

	public:

		virtual ~enum_class ();

//		operator value_type () const;
		operator value_type const & () const;

		static const_iterator begin ();
		static const_iterator end ();

};

template < typename T , typename B >
bool operator< ( enum_class<T,B> const & lhs , enum_class<T,B> const & rhs );

}

#include "enum_class.inl"

#endif

