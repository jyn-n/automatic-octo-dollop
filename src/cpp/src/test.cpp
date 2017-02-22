
#include "game_object.hpp"

#include <iostream>

game_object foo ( game_object && g ) { return std::move (g); }

int main () {

	game_object::object_base_type b;

	game_object g ( b );
	game_object h ( b );

	game_object i = foo ( std::move(h) );


	return 0;
}
