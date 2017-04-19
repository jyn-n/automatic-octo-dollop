
#include "game.hpp"

#include "common/iterator_range.hpp"

namespace game {

namespace stdp = std::placeholders;

#ifdef PSTACK
	static_assert ( false );
#endif

#define PSTACK(l) stack_location ( player , player_location::l )

game::game ( event_manager_type & event_manager , count_type const & n_players , rng_type & rng )
: _players ()
, _base_player ()
, _cardworld ()
, _event_manager ( event_manager )
, _rng ( rng )
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

auto game::cardworld () const -> cardworld_type const &
{
	return _cardworld;
}

template < typename T >
auto game::move ( card_location_type<T> const & origin , stack_location_type const & destination ) -> key_card_location_type
{
	return _cardworld.move ( origin , destination );
}

auto game::move ( any_card_location_type const & origin , stack_location_type const & destination ) -> key_card_location_type 
{
	return move_any ( origin , destination );
}

template auto game::move <game::cardworld_type::key_type> ( card_location_type<cardworld_type::key_type> const & origin , stack_location_type const & destination ) -> key_card_location_type;
template auto game::move <game::cardworld_type::order_type> ( card_location_type<cardworld_type::order_type> const & origin , stack_location_type const & destination ) -> key_card_location_type;

auto game::move_any ( any_card_location_type const & origin , stack_location_type const & destination ) -> key_card_location_type
{
	if (origin.valid_key())
		return move ( origin.key() , destination );
	else
		return move ( origin.order() , destination );
}

auto game::reveal ( object_type const & player ) -> void
{
	move_top_reshuffling ( PSTACK ( deck ) , PSTACK ( reveal ) , PSTACK ( discard ) );
}

auto game::play ( object_type const & player , any_card_location_type const & card ) -> void
{
	move ( card , PSTACK ( play ) );
	//_event_manager.operator() < event_name::move_card , any_card_location_type const & , stack_location_type const & > ( card , PSTACK ( play ) );

	//TODO reveal check
}

auto game::cleanup_cardplay ( object_type const & player ) -> void
{
	move_location ( PSTACK ( play ) , PSTACK ( discard ) );
	move_location ( PSTACK ( reveal ) , PSTACK ( discard ) );
}

auto game::discard ( object_type const & player , any_card_location_type const & card ) -> void
{
	move_any ( card , PSTACK ( discard ) );
}

auto game::move_top ( stack_location_type const & origin , stack_location_type const & destination ) -> bool
{
	if ( _cardworld [ origin ].size() > 0 ) {
		//_event_manager.operator()< event_name::move_card , any_card_location_type const & , stack_location_type const & > ( order_card_location_type ( origin , 0 ) , destination );
		move ( order_card_location_type ( origin , 0 ) , destination );
		return false;
	}
	return true;
}

auto game::move_location ( stack_location_type const & origin , stack_location_type const & destination ) -> void
{
	auto & origin_stack = _cardworld [ origin ];
	while ( origin_stack.size() > 0 )
		move_top ( origin , destination );
}

auto game::register_events () -> this_type &
{
	_event_manager.register_event<event_name::reshuffle> ( event_manager_type::event_type < stack_location_type const & , stack_location_type const & > ( std::bind ( &game::reshuffle , this , stdp::_1 , stdp::_2 ) ) );
	_event_manager.register_event<event_name::move_card> ( event_manager_type::event_type < any_card_location_type const & , stack_location_type const & > ( std::bind ( &game::move_any , this , stdp::_1 , stdp::_2 ) ) );

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

auto game::reshuffle ( stack_location_type const & origin , stack_location_type const & destination ) -> void
{
	move_location ( origin , destination );
	_cardworld [ destination ].shuffle ( _rng );
}

auto game::move_top_reshuffling ( stack_location_type const & origin , stack_location_type const & destination , stack_location_type const & reshuffle_origin ) -> bool
{
	if ( ! move_top ( origin , destination ) ) return false;

	//_event_manager.operator()<event_name::reshuffle , stack_location_type const & , stack_location_type const & > ( reshuffle_origin , origin );
	reshuffle ( reshuffle_origin , origin );

	return move_top ( origin , destination );
}

}

