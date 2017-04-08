
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>
#include <map>

#include "common/id_factory.hpp"

namespace core {

class game_object {

	public:

		using this_type = game_object;

		using id_type = unsigned long;
		using key_type = std::string;
		using value_type = signed long;

		using object_base_type = std::map < key_type , value_type >;

	private:

		using container_type = std::map < key_type , value_type >;
		using id_factory_type = common::id_factory < id_type >;

		object_base_type const & _base;
		container_type _attributes;
		id_type _id;

		bool _valid;

		static id_factory_type _id_factory;

	public:

		game_object ( object_base_type const & base );
		~game_object () noexcept ;

		game_object ( this_type && rhs );
		game_object ( this_type const & ) = delete;

		//bool operator== ( this_type const & rhs ) const;

		value_type const & at ( key_type const & key ) const;
		value_type & operator[] ( key_type const & key );

		id_type const & id () const;

};

}

#endif

