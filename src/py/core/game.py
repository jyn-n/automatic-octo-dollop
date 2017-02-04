
import .game_object_type , .game_object , .cardworld
from common import player_location as pl

class game:

	def __init__ ( self , players ):
		self._player = game_object_type()
		for l in pl:
			self._player [l] = (l,)

		self._players = dict()

		for i in range(players):
			player = game_object ( self._player )
			self._players [ player.id() ] = player

		self._cardworld = cardworld()

		for player in self._players:
			for location in pl:
				self._cardworld [ self.location ( player , location) ]

	def players ( self ):
		return self._players.values()

	def location ( self , player , location ):
		return cardworld.location ( (str(player.id()),) , None , player[location] )

	def cardworld ( self ):
		return self._cardworld

	def move_card ( self , origin , destination ):
		destination = self._cardworld.move ( origin , destination )
		#TODO publish ( moved , origin , destination )

	def _move_top ( self , player , origin , destination ):
		origin = self.location ( player , origin )
		destination = self.location ( player , destination )

		if len ( self._cardworld [ deck ].cardstack() ) > 0
			self.move_card (
				cardworld.card_location (
					origin,
					0
				)
				destination
			)
			return False
		return True

	def _move_location ( self , player , origin , destination ):
		origin = self.location ( player , origin )
		destination = self.location ( player , destination )

		while len ( self._cardworld [ origin ].cardstack() ) > 0:
			self._move_top ( player , origin , destination )

	def _move_top_reshuffling ( self , player , origin , destination ):
		if not self._move_top ( player , origin , destination ):
			return False

		self._move_location ( player , destination , origin )
		self._cardworld [ origin ].cardstack().shuffle()

		return self._move_top ( player , origin , destination )

	def draw ( self , player ):
		return self._move_top_reshuffling ( player , pl.deck , pl.hand )

	def reveal ( self , player ):
		return self._move_top_reshuffling ( player , pl.deck , pl.reveal )

