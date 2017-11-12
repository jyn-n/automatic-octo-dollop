
#include "game/game.hpp"

#include <iostream>

#include <random>
/*
template < typename T >
void print ( T const & t )
{
	for ( auto const & x : t ) std::cout << x << ' ';
	std::cout << '\n';
}

std::ostream & operator<< ( std::ostream & out , core::game_object const & obj )
{
	return out << obj.id();
}

template < typename First , typename Second >
std::ostream & operator<< ( std::ostream & out , std::pair<First,Second> const & pair )
{
	return out << '(' << pair.first << ',' << pair.second << ')';
}

std::ostream & operator<< ( std::ostream & out , game::player_location const & loc )
{
	return out << static_cast < std::string > (loc);
}

std::ostream & operator<< ( std::ostream & out , game::location const & loc )
{
	return out << static_cast < std::string > (loc);
}
*/
int main () {

	std::random_device seed;
	std::mt19937_64 rng { seed () };

/*
	core::game_object::object_base_type b;

	core::cardworld world;

	core::cardworld::stack_location s1 { "foo" , "bar" } ;
	core::cardworld::stack_location s2 { "foo" , "quux" } ;

	world[s1];
	world[s2];

	auto l = world.insert ( s1 , core::game_object (b) );
	world.move ( l , s2 );

	world.insert ( s2 , core::game_object (b) );
	world.insert ( s2 , core::game_object (b) );
	world.insert ( s2 , core::game_object (b) );
	world.insert ( s2 , core::game_object (b) );
	world.insert ( s2 , core::game_object (b) );

	world[s2].shuffle(rng);

	print ( world.at(s2) );

	l = world.move ( s2 , 0 , s1 );
	l = world.move ( s2 , 2 , s1 );

	print ( world.at(s1) );
	print ( world.at(s2) );
*/
/*
	print ( common::make_range ( game::player_location::begin() , game::player_location::end() ) );
	print ( common::make_range ( game::location::begin() , game::location::end() ) );

	{
		game::player_location q ( "bar" );
		print ( common::make_range ( game::player_location::begin() , game::player_location::end() ) );
	}

	print ( common::make_range ( game::player_location::begin() , game::player_location::end() ) );
*/

	game::game::event_manager_type event_manager;
	game::game ( event_manager , 1 , seed );

	std::cout << "bar\n";

	return 0;
}

