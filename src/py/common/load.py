
import yaml

from common import directories
from core import game_object_type , game_object , cardstack as Cardstack

class _type_file: pass

def load_type_dir ( path ):
	def load_type ( path ):
		file_ = yaml.load ( path )
		return file_.name , game_object_type ( file_.attributes )

	result = dict()
	for filename in path.glob ( directories.card_type_expression ):
		with filename.open() as f:
			try:
				result.update ( [load_type ( f )] )
			except:
				print ( 'error reading file ' + f )
	return result

def _game_objects ( types , typenames ):
	return [ game_object ( types [ name ] ) for name in typenames ]

def load_deck ( path , card_types ):
	def decklist ( d ):
		def flatten ( t ):
			if len(t) == 0: return []
			return t[0] + flatten(t[1:])

		return flatten ( [ [c] * n for c , n in d.items() ] )

	def cardstack ( d ):
		result = Cardstack()
		for o in _game_objects ( card_types , decklist(d) ):
			result.insert(o)
		return result

	with path.open() as f:
		result = { k : cardstack(v) for k,v in yaml.load ( f ).items() }

	return result

