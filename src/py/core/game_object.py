
from .id_factory import id_factory

class game_object:

	next_id = id_factory()

	def __init__( self , type_ ):
		self._type = type_
		self._attributes = dict()
		self._id = self.next_id()

	def __getitem__ ( self , key ):
		if self._attributes.keys().isdisjoint ( [key] ):
			return self._type[key]
		return self._attributes[key]

	def __setitem__ ( self , key , value ):
		self._attributes[key] = value

	def id (self):
		return self._id

