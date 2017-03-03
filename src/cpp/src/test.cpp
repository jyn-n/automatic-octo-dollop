
#include "core/cardworld.hpp"

#include <iostream>

#include <random>

template < typename T >
void print ( T const & t )
{
	for ( auto const & x : t ) std::cout << x << ' ';
	std::cout << '\n';
}

std::ostream & operator<< ( std::ostream & out , game_object const & obj )
{
	return out << obj.id();
}

template < typename First , typename Second >
std::ostream & operator<< ( std::ostream & out , std::pair<First,Second> const & pair )
{
	return out << '(' << pair.first << ',' << pair.second << ')';
}

template < typename RNG >
void foo ( RNG && rng )
{
	std::cout << rng() << '\n';
}

int main () {

	std::random_device seed;
	std::mt19937_64 rng { seed () };

	game_object::object_base_type b;

	cardworld world;

	cardworld::stack_location s1 { "foo" , "bar" } ;
	cardworld::stack_location s2 { "foo" , "quux" } ;

	world[s1];
	world[s2];

	auto l = world.insert ( s1 , game_object (b) );
	world.move ( l , s2 );

	world.insert ( s2 , game_object (b) );
	world.insert ( s2 , game_object (b) );
	world.insert ( s2 , game_object (b) );
	world.insert ( s2 , game_object (b) );
	world.insert ( s2 , game_object (b) );

	world[s2].shuffle(rng);

	print ( world.at(s2) );

	l = world.move ( s2 , 0 , s1 );
	l = world.move ( s2 , 2 , s1 );

	print ( world.at(s1) );
	print ( world.at(s2) );

	for (int i = 0; i != 10; ++i) foo (rng);

	return 0;
}

