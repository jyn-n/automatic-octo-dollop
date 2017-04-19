
#ifndef GAME_HPP
#define GAME_HPP

#include "common/event_manager.hpp"

#include "location.hpp"
#include "player_location.hpp"

#include "event.hpp"

#include "core_types.hpp"

#include <map>

namespace game {

class game {

	public:

		using this_type = game;

		using object_type = core_types::object_type;
		using object_base_type = core_types::object_base_type;

		using event_manager_type = common::event_manager < event_name , event_parameter_list  >;

		using id_type = core_types::id_type;

		template < typename T >
		using card_location_type = core_types::card_location_type<T>;
		using stack_location_type = core_types::stack_location_type;
		using key_card_location_type = core_types::key_card_location_type;
		using order_card_location_type = core_types::order_card_location_type;
		using any_card_location_type = core_types::any_card_location_type;

		using rng_type = core_types::rng_type;

	private:

		using cardworld_type = core_types::cardworld_type;
		using player_container_type = std::map < id_type , object_type >;

	public:

		using count_type = player_container_type::size_type;

	private:

		player_container_type _players;
		object_base_type _base_player;

		cardworld_type _cardworld;

		event_manager_type & _event_manager;

		rng_type & _rng;

		template < typename T >
		key_card_location_type move ( card_location_type<T> const & origin , stack_location_type const & destination );
		key_card_location_type move_any ( any_card_location_type const & origin , stack_location_type const & destination );
		key_card_location_type move ( any_card_location_type const & origin , stack_location_type const & destination );
		void reshuffle ( stack_location_type const & origin , stack_location_type const & destination );
		void reveal ( object_type const & player );
		void play ( object_type const & player , any_card_location_type const & card );
		void cleanup_cardplay ( object_type const & player );
		void discard ( object_type const & player , any_card_location_type const & card );

	public:

		game ( event_manager_type & event_manager , count_type const & n_players , rng_type & rng );

		stack_location_type stack_location ( object_type const & player , player_location loc ) const;

		cardworld_type const & cardworld () const;

		bool move_top ( stack_location_type const & origin , stack_location_type const & destination );
		void move_location ( stack_location_type const & origin , stack_location_type const & destination );

		bool move_top_reshuffling ( stack_location_type const & origin , stack_location_type const & destination , stack_location_type const & reshuffle_origin );

	private:

		this_type & register_events ();
		this_type & create_players ( count_type const & n_players );
		this_type & create_locations ();

};

}

#include "game.inl"

#endif

