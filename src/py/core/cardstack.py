
from random import shuffle

class cardstack:

	def __init__ ( self ):
		self._items = dict()
		self._order = list()

	def __len__ ( self ):
		return len ( self._items )

	def __getitem__ ( self , ident ):
		return self._items[self._to_key(ident)]

	def __iter__ ( self ):
	#	class iterator:
	#		def __init__ ( inner_self ):
	#			inner_self._iter = iter(self._order)

	#		def __next__ ( inner_self ):
	#			try:
	#				return self._items[next(inner_self._iter)]
	#			except StopIteration:
	#				raise StopIteration()

	#	return iterator()
		return iter(self._order)

	@staticmethod
	def _is_key ( key ):
		return type(key) == str

	def _to_key ( self , pos ):
		if self._is_key ( pos ):
			return pos
		return self._order[pos]


	def insert ( self , value , position = None ):
		if position is None:
			position = len(self._order)
		key = value.id()
		self._items [ key ] = value
		self._order.insert( position , key )
		return key

	def erase ( self , ident ):
		key = self._to_key(ident)

		if self._items.keys().isdisjoint( [key] ):
			raise KeyError(key)

		self._order.remove(key)

		return self._items.pop(key)

	def shuffle ( self ):
		shuffle ( self._order )

	def find ( self , card ):
		for key , value in self._items.items():
			if value == card:
				return key
		return None

