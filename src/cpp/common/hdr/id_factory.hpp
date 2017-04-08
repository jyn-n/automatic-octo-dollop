
#ifndef ID_FACTORY_HPP
#define ID_FACTORY_HPP

#include <set>

namespace common {

template < typename T >
class id_factory {

	public:

		using this_type = id_factory < T >;
		using id_type = T;

	private:

		using container_type = std::set < id_type >;

		id_type _current;
		container_type _free_ids;

	public:

		id_factory ();

		id_type operator() ();
		this_type & free ( id_type id );

};

}

#include "id_factory.inl"

#endif

