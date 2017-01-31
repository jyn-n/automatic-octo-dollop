from PyQt4 import QtGui , QtCore

class FactorWidth:

	def __init__ ( self , factor ):
		self._factor = factor

	def __call__ ( self , rect ):
		return rect.height() * self._factor


class ConstWidth:

	def __init__ (self , value ):
		self._value = value

	def __call__ ( self , rect ):
		return self._value


class OverlapLayout (QtGui.QLayout):

	def __init__ ( self , parent = None , item_width_idea = FactorWidth(1) ):
		super().__init__(parent)
		self._items = list()
		self.set_item_width_idea ( item_width_idea )

	def set_item_width_idea ( self , item_width_idea ):
		self._item_width_idea = item_width_idea

	def _item_width ( self ):
		return self._item_width_idea ( self.geometry() )

	def addItem ( self , item ):
		self._items.append( item )

	def count ( self ):
		return len(self._items)

	def itemAt ( self , i ):
		if i in range(0, self.count()):
			return self._items[i]
		return None

	def takeAt ( self , i):
		del self._items[i]

	def _space ( self ):
		width = self._item_width ()
		if self.count() > 1:
			return min ( (self.geometry().width() - width) / ( self.count() - 1 ) , width )
		return width

	def setGeometry ( self , rect ):
		super().setGeometry ( rect )

		for i in range(0 , self.count()):
			self._items[i].setGeometry ( QtCore.QRect ( i * self._space() , 0 , self._item_width () , rect.height() ))

	def sizeHint ( self ):
		return QtCore.QSize ( self._space () * ( self.count() - 1 ) + self._item_width () , self.geometry().height() )

