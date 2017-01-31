
class cardworld_gui:

	def __init__ ( self ):
		self._cardlistwidgets = dict()

	def __setitem__ ( self , location , widget ):
		self._cardlistwidgets [ location ] = widget

	def __getitem__ ( self , location ):
		return self._cardlistwidgets [ location ]

	def move ( self , origin , destination , card ):
		if not self._cardlistwidgets.keys().isdisjoint ([ origin ]):
			self._cardlistwidgets [origin].erase (card)

		if not self._cardlistwidgets.keys().isdisjoint ([ destination ]):
			self._cardlistwidgets [destination].insert (card)

