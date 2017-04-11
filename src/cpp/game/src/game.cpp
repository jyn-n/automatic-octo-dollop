
#include "game.hpp"

//#include "event_context.hpp"

//#include "common/iterator_range.hpp"

namespace game {
/*
game::game ( event_manager_type & event_manager , count_type const & n_players )
: _players ()
, _base_player ()
, _cardworld ()
, _event_manager ( event_manager )
{
	register_events();
	create_players ( n_players );
	create_locations ();
}

auto game::stack_location ( object_type const & player , player_location loc ) const -> stack_location_type 
{
	if ( ! _players.count ( player.id() ) ) throw 1;

	return stack_location_type ( { location::player , std::to_string ( player.id() ) , loc } );
}

auto game::register_events () -> this_type &
{
	//TODO

	return *this;
}

auto game::create_players ( count_type const & n_players ) -> this_type &
{
	for ( auto i = n_players; i > 0; ++i ) {
		object_type player ( _base_player );
		_players.insert ( std::make_pair ( player.id() , std::move ( player ) ) );
	}
	return *this;
}

auto game::create_locations () -> this_type &
{
	for ( auto const & player : _players ) {
		for ( auto const & loc : common::make_range ( player_location::begin() , player_location::end() ) ) {
			_cardworld [ stack_location ( player.second , loc ) ];
		}
	}

	return *this;
}
*/
}

