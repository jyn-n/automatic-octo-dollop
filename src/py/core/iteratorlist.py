
from copy import deepcopy

class iteratorlist:
	def __init__ ( self , iterators ):
		self._iterators = iterators

	def __next__ ( self ):
		while len(self._iterators) > 0:
			try:
				return next(self._iterators[0])
			except StopIteration:
				del self._iterators[0]
		raise StopIteration()

	def clone ( self ):
		return deepcopy(self)

