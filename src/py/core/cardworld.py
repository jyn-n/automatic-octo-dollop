
from .iteratorlist import iteratorlist
from .cardstack import cardstack

class cardworld:

	class location:
		def __init__ ( self , keys , inside = None , outside = None):
			iters = list()
			for l in [ outside , keys , inside ]:
				if l is None:
					continue
				iters.append(iter(l))

			self._iter = iteratorlist(iters)

		def __iter__ ( self ):
			return self._iter.clone()

	class card_location:
		def __init__ ( self , stack_location , card_identifier ):
			self._stack_location = stack_location
			self._card_identifier = card_identifier

		def stack ( self ):
			return self._stack_location

		def card ( self ):
			return self._card_identifier

	def __init__ ( self ):
		self._items = dict()
		self._cards = cardstack()

	def cardstack ( self ):
		return self._cards

	def __getitem__ ( self , loc ):
		if type(loc) == cardworld.card_location:
			return self.resolve_card ( loc )
		return self.resolve_location ( loc )

	def resolve_location ( self , loc ):
		return self._resolve_iterator ( iter(loc) )

	def resolve_card ( self , loc ):
		return self[loc.stack()]._cards[loc.card()]

	def _resolve_iterator ( self , iterator ):
		try:
			current = next(iterator)
		except StopIteration:
			return self

		if self._items.keys().isdisjoint ( [current] ):
			self._items[current] = cardworld()

		return self._items[current]._resolve_iterator(iterator)

	def insert ( self , loc , card ):
		return cardworld.card_location ( loc , self[loc]._cards.insert(card) )

	def erase ( self , loc ):
		return self[loc.stack()]._cards.erase(loc.card())

	def move ( self , source , destination ):
		return self.insert ( destination , self.erase ( source ) )

