
class cardworld_gui:

	def __init__ ( self ):
		self._cardlistwidgets = dict()

	def __setitem__ ( self , location , widget ):
		self._cardlistwidgets [ tuple(location) ] = widget

	def __getitem__ ( self , location ):
		return self._cardlistwidgets [ location ]

	def move ( self , origin , destination , card ):
		origin , origin_location = tuple(origin.stack()) , origin.card()
		destination , destination_location = tuple(destination.stack()) , destination.card()

		if not self._cardlistwidgets.keys().isdisjoint ([ origin ]):
			self._cardlistwidgets [origin].erase (origin_location)

		if not self._cardlistwidgets.keys().isdisjoint ([ destination ]):
			self._cardlistwidgets [destination].insert (destination_location , card)

	def update ( self , world ):
		for location , widget in self._cardlistwidgets.items():
			widget.update_cards ( world [ location ].cardstack() , location )

