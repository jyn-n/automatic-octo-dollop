
#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP

#include "core/game_object.hpp"
#include "core/cardworld.hpp"

#include <random>

namespace game {
	namespace core_types {
		using object_type = core::game_object;
		using object_base_type = object_type::object_base_type;
		using id_type = object_type::id_type;
		using cardworld_type = core::cardworld;
		using cardstack_type = core::cardstack;
		using key_type = cardworld_type::key_type;
		using stack_location_type = cardworld_type::stack_location;
		template < typename T >
		using card_location_type = cardworld_type::card_location<T>;
		using key_card_location_type = cardworld_type::key_card_location;
		using order_card_location_type = cardworld_type::order_card_location;
		using any_card_location_type = cardworld_type::any_card_location;

		using rng_type = std::random_device;
	}
}

#endif

