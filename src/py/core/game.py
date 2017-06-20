
from .game_object_type import game_object_type
from .game_object import game_object
from .cardworld import cardworld
from common import player_location as pl , event as e , card_attribute as ca
from functools import partial
from common import location as loc

class game:

	def __init__ ( self , players , event ):
		self._player = game_object_type()
		for location in dir(pl):
			if location.startswith('__'): continue
			self._player [location] = (location,)

		self._players = dict()

		for i in range(players):
			player = game_object ( self._player )
			self._players [ player.id() ] = player

		self._cardworld = cardworld()

		for player in self._players.values():
			for location in dir(pl):
				if location.startswith('__'): continue
				self._cardworld [ self.location ( player , location) ]

		self._event = event

		event.register_event ( e.reshuffle , self.reshuffle )
		event.register_event ( e.move_card , self.move_card )
		event.register_event ( e.reveal , self.reveal )
		event.register_event ( e.play , self.play )
		event.register_event ( e.cleanup_cardplay , self.cleanup_cardplay )
		event.register_event ( e.discard , self.discard )

	def players ( self ):
		return self._players.values()

	def load_deck ( self , player , deck ):
		for location , cards in deck.items():
			self._cardworld [ self.location ( player , location ) ].stack ( cards )

	def location ( self , player , location ):
		return cardworld.location ( ( loc.player , str(player.id()) ) , player[location] )

	def cardworld ( self ):
		return self._cardworld

	def move_card ( self , origin , destination ):
		origin = cardworld.card_location ( origin.stack() , self.cardworld() [ origin.stack() ].cardstack()._to_key ( origin.card() ) )
		self._event ( e.pre_card_move , origin , destination )
		destination = self._cardworld.move ( origin , destination )
		self._event ( e.post_card_move , origin , destination )

	def _move_top ( self , origin , destination ):
		if len ( self._cardworld [ origin ].cardstack() ) > 0:
			self._event (
				e.move_card,
				cardworld.card_location (
					origin,
					0
				),
				destination
			)
			return False
		return True

	def _move_location ( self , origin , destination ):

		while len ( self._cardworld [ origin ].cardstack() ) > 0:
			self._move_top ( origin , destination )

	def reshuffle ( self , origin , destination ):
		self._move_location ( origin , destination )
		self._cardworld [ destination ].cardstack().shuffle()

	def _move_top_reshuffling ( self , origin , destination , reshuffle_origin ):
		if not self._move_top ( origin , destination ):
			return False

		self._event ( e.reshuffle , reshuffle_origin , origin )

		return self._move_top ( origin , destination )

	def draw ( self , player ):
		location = partial ( self.location , player )

		return self._move_top_reshuffling (
			location ( pl.deck ),
			location ( pl.hand ),
			location ( pl.discard )
		)

	def reveal ( self , player ):
		location = partial ( self.location , player )

		return self._move_top_reshuffling (
			location ( pl.deck ),
			location ( pl.reveal ),
			location ( pl.discard )
		)

	def play ( self , player , card_location ):
		card = self.cardworld() [ card_location ]
		self._event ( e.move_card , card_location , self.location ( player , pl.play ) )

		for i in range ( card [ ca.check_size ] ):
			self._event ( e.reveal , player )

		self.draw ( player )

		self._event ( e.post_play )

	def cleanup_cardplay ( self , player ):
		location = partial ( self.location , player )

		discard = location ( pl.discard )
		self._move_location ( location ( pl.play ) , discard )
		self._move_location ( location ( pl.reveal ) , discard )

	def discard ( self , player , card_location ):
		self.move_card ( card_location , self.location ( player , pl.discard ) )

