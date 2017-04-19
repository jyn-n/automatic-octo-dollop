
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
	cleanup_cardplay,

	pre_move_card,
	post_move_card,
	pre_play,
	post_play
};

template < event_name name >
class event_parameter_list;

#ifdef PARAMETER_LIST
	static_assert ( false );
#endif

#define PARAMETER_LIST(name,...) template <> class event_parameter_list < event_name::name > { public: event_parameter_list() = delete; using type = common::typelist<__VA_ARGS__>; }

PARAMETER_LIST( move_card , core_types::any_card_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( reshuffle , core_types::stack_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( reveal , core_types::object_type const & ); // player
PARAMETER_LIST( discard , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card
PARAMETER_LIST( draw , core_types::object_type const & ); // player
PARAMETER_LIST( play , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card
PARAMETER_LIST( cleanup_cardplay , core_types::object_type const & ); // player

PARAMETER_LIST( pre_move_card , core_types::any_card_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( post_move_card , core_types::any_card_location_type const & , core_types::stack_location_type const & ); // origin , destination
PARAMETER_LIST( pre_play , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card
PARAMETER_LIST( post_play , core_types::object_type const & , core_types::any_card_location_type const & ); // player , card

#undef PARAMETER_LIST

}

#endif

