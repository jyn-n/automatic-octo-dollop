
class id_factory:

	def __init__ ( self ):
		self._current_id = 0

	def __call__ ( self ):
		result = self._current_id
		self._current_id += 1
		return str(result)

