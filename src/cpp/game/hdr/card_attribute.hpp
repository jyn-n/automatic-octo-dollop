
#ifndef CARD_ATTRIBUTE_HPP
#define CARD_ATTRIBUTE_HPP

#include "common/enum_class.hpp"
#include "core_types.hpp"

namespace game {

class card_attribute : public common::enum_class<core_types::key_type, card_attribute>
{
	public:

		card_attribute ( value_type && value_type );
		virtual ~card_attribute ();

		static card_attribute const title;
		static card_attribute const effect;
		static card_attribute const time;
		static card_attribute const check_size;
		static card_attribute const successes;
};

}

#endif

