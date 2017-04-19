
#ifndef EVENT_HPP
#define EVENT_HPP

#include "common/event_manager.hpp"

#include "core_types.hpp"

namespace game {

enum class event_name
{
	move_card,
	reshuffle,
	reveal,
	discard,
	draw,
	play,
	cleanup_cardplay
};

template < event_name name >
class event_parameter_list;

#ifdef PARAMETER_LIST
	static_assert ( false );
#endif

#define PARAMETER_LIST(name,...) template <> class event_parameter_list < name > { public: event_parameter_list() = delete; using type = common::typelist<__VA_ARGS__>; }

PARAMETER_LIST( event_name::move_card , core_types::any_card_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( event_name::reshuffle , core_types::stack_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( event_name::reveal , core_types::object_type const & ); // player
PARAMETER_LIST( event_name::discard , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card
PARAMETER_LIST( event_name::draw , core_types::object_type const & ); // player
PARAMETER_LIST( event_name::play , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card
PARAMETER_LIST( event_name::cleanup_cardplay , core_types::object_type const & ); // player

#undef PARAMETER_LIST

}

#endif

