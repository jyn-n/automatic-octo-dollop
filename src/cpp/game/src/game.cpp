
#include "game.hpp"

#include "common/iterator_range.hpp"

#include "card_attribute.hpp"

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

auto game::stack_location ( object_type const & player , player_location const & loc ) const -> stack_location_type 
{
	if ( ! _players.count ( player.id() ) ) throw 1;

	return stack_location_type ( { location::player , std::to_string ( player.id() ) , loc } );
}

auto game::cardworld () const -> cardworld_type const &
{
	return _cardworld;
}

template < typename T >
auto game::_move ( card_location_type<T> const & origin , stack_location_type const & destination ) -> void
{
	_cardworld.move ( origin , destination );
}

template auto game::_move <game::cardworld_type::key_type> ( card_location_type<cardworld_type::key_type> const & origin , stack_location_type const & destination ) -> void;
template auto game::_move <game::cardworld_type::order_type> ( card_location_type<cardworld_type::order_type> const & origin , stack_location_type const & destination ) -> void;

auto game::move ( any_card_location_type const & origin , stack_location_type const & destination ) -> void
{
	_event_manager.operator() < event_name::pre_move_card > ( std::cref(origin) , std::cref(destination) );

	if (origin.valid_key())
		_move ( origin.key() , destination );
	else
		_move ( origin.order() , destination );

	_event_manager.operator() < event_name::post_move_card > ( std::cref(origin) , std::cref(destination));
}

auto game::reveal ( object_type const & player ) -> void
{
	move_top_reshuffling ( PSTACK ( deck ) , PSTACK ( reveal ) , PSTACK ( discard ) );
}

auto game::play ( object_type const & player , any_card_location_type const & card ) -> void
{
	_event_manager.operator()< event_name::pre_play > ( std::cref(player) , std::cref(card) );

	move ( card , PSTACK ( play ) );

	for ( auto i = _cardworld [ card ] [ card_attribute::successes ]; i > 0; ++i )
		reveal ( player );

	_event_manager.operator()< event_name::post_play > ( std::cref(player) , std::cref(card) );
}

auto game::cleanup_cardplay ( object_type const & player ) -> void
{
	move_location ( PSTACK ( play ) , PSTACK ( discard ) );
	move_location ( PSTACK ( reveal ) , PSTACK ( discard ) );
}

auto game::discard ( object_type const & player , any_card_location_type const & card ) -> void
{
	move ( card , PSTACK ( discard ) );
}

auto game::move_top ( stack_location_type const & origin , stack_location_type const & destination ) -> bool
{
	if ( _cardworld [ origin ].size() > 0 ) {
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
	_event_manager.register_event<event_name::reshuffle> ( std::bind ( &game::reshuffle , this , stdp::_1 , stdp::_2 ) );
	_event_manager.register_event<event_name::move_card> ( std::bind ( &game::move , this , stdp::_1 , stdp::_2 ) );
	_event_manager.register_event<event_name::reveal> ( std::bind ( &game::reveal , this , stdp::_1 ) );
	_event_manager.register_event<event_name::play> ( std::bind ( &game::play , this , stdp::_1, stdp::_2 ) );
	_event_manager.register_event<event_name::cleanup_cardplay> ( std::bind ( &game::cleanup_cardplay , this , stdp::_1 ) );
	_event_manager.register_event<event_name::discard> ( std::bind ( &game::discard , this , stdp::_1 , stdp::_2 ) );

	return *this;
}

auto game::create_players ( count_type const & n_players ) -> this_type &
{
	for ( auto i = n_players; i > 0; --i ) {
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

	reshuffle ( reshuffle_origin , origin );

	return move_top ( origin , destination );
}

#undef PSTACK

}

