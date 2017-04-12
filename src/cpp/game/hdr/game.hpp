
#ifndef GAME_HPP
#define GAME_HPP

#include "core/game_object.hpp"
#include "core/cardworld.hpp"

#include "common/event_manager.hpp"

#include "location.hpp"
#include "player_location.hpp"

#include <map>

namespace game {

class event_context;

class game {

	public:

		using this_type = game;

		using object_type = core::game_object;
		using object_base_type = object_type::object_base_type;

		using event_manager_type = common::event_manager < event_context >;

		using count_type = unsigned long;
		using id_type = object_type::id_type;

	private:

		using cardworld_type = core::cardworld;

		using player_container_type = std::map < id_type , object_type >;

	public:

		using stack_location_type = cardworld_type::stack_location;
		//using card_location_type = cardworld_type::card_location;

	private:

		player_container_type _players;
		object_base_type _base_player;

		cardworld_type _cardworld;

		event_manager_type & _event_manager;

	public:

		game ( event_manager_type & event_manager , count_type const & n_players );

		stack_location_type stack_location ( object_type const & player , player_location loc ) const;

	private:

		this_type & register_events ();
		this_type & create_players ( count_type const & n_players );
		this_type & create_locations ();

};

}

#endif

